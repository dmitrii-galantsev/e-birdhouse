(ns ring-server.core
  (:require [ring.adapter.jetty :as jetty]
            [ring.util.request :as req]
            [clj-postgresql.core :as pg]
            [clojure.java.jdbc :as jdbc])
  (:gen-class))

;
; RESTful processor
;

(defn post_handler [request]
  (str "POST \nquery:"
       (request :query-string)
       " \nbody:"
       (req/body-string request)))

; there has to be a better way to write this
; maps request-method to a handler function
(def handler_map {:get  #(str "GET "  %)
                  :post #(post_handler %)})

; returns a function which handles the request
(defn match_requests [request-method]
  (def k (handler_map request-method))
  (if (nil? k) ; if method isn't matched -> show unknown message
    #(str "REQUEST-METHOD: UNKNOWN" (% :query-string))
    k))

(defn handler [request]
  {:status 200
   :headers {"Content-Type" "text/html"}
   ; get and execute the handler function
   :body ((match_requests (:request-method request)) request)})

;
; PostgreSQL processor
;

; define DB connection
(def db
  (pg/pool :host "popi.tech" :user "bird" :dbname "bird" :password "bird"))

; check if data type is a vector of 4 digits
(defn insert_type_check [values]
  (and
    (= (type values) clojure.lang.PersistentVector)
    (= (count values) 4)))

; convert vector into postgresql row
(defn vec_to_row [vec]
  (def k (apply str (map #(str % ", ") vec)))
  (str "(" (subs k 0 (- (count k) 2)) ")"))

; insert data into the DB. doesn't return anything
(defn db_insert [values]
  (if (insert_type_check values)
    (jdbc/query db (str "INSERT INTO dev VALUES " (vec_to_row values)))))

;
; Main
;

(defn -main
  [& args]
  (jetty/run-jetty handler {:port 3000}))
