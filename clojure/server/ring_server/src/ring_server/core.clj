(ns ring-server.core
  (:require [ring.adapter.jetty :as jetty]
            [ring.util.request :as req])
  (:gen-class))

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

(defn -main
  [& args]
  (jetty/run-jetty handler {:port 3000}))
