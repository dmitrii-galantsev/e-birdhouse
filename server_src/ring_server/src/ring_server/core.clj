(ns ring-server.core
  (:require [ring.adapter.jetty :as jetty]
            [ring.util.request :as req]
            [ring.util.response :as resp]
            [clj-postgresql.core :as pg]
            [clojure.java.jdbc :as jdbc])
  (:gen-class))

(use 'ring.middleware.params)

; TODO add timestamp
; define temporary day
(def day 0)

;
; PostgreSQL processor
;

; define DB connection
(def db
  (pg/pool :host "localhost" :user "bird" :dbname "bird" :password "bird"))

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
; RESTful processor
;
; TODO: this will return an error because postgresDB doesn't respond.
; it will still work.
(defn post_handler [request]
  (let [my_params ((params-request request) :params)]
    (def day (inc day))
    (db_insert [(str day) (my_params "temp") (my_params "hum") "0"])
    (str "POST \nquery:"
         my_params
         " \nbody:"
         (req/body-string request))))


; there has to be a better way to write this
; maps request-method to a handler function
(def handler_map {:get  #(str "GET "  %)
                  :post #(post_handler %)})


; returns a function which handles the request
(defn match_requests [request-method]
  (let [func (handler_map request-method)]
    (if (nil? func) ; if method isn't matched -> show unknown message
      #(str "REQUEST-METHOD: UNKNOWN" (% :query-string))
      func)))

; get and execute the handler function
(defn handler [request]
  (-> (resp/response ((match_requests (:request-method request)) request))
      (resp/content-type "text/plain")))

;  (-> (resp/response ((match_requests (:request-method request)) request))
;      (resp/content-type "text/plain")))

;
; Main
;

(defn -main
  [& args]
  (jetty/run-jetty handler {:port 3000}))
