(ns ring-server.core
  (:require [ring.adapter.jetty :as jetty])
  (:gen-class))

(def requests_map {:get  "GET"
                   :post "POST"})

(defn match_requests [request-method]
  (def k (requests_map request-method))
  (if (nil? k) ; if method isn't matched -> show unknown message
    "REQUEST-METHOD: UNKNOWN"
    k))


(defn handler [request]
  {:status 200
   :headers {"Content-Type" "text/html"}
   :body (match_requests (:request-method request))})

(defn -main
  [& args]
  (jetty/run-jetty handler {:port 3000}))