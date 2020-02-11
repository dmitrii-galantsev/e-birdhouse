(defproject ring_server "0.1.0-SNAPSHOT"
  :description "receive POST and add to DB"
  :license {:name "Eclipse Public License"
            :url "http://www.eclipse.org/legal/epl-v10.html"}
  :dependencies [[org.clojure/clojure "1.8.0"]
                 [clj-postgresql "0.7.0"]
                 [ring "1.8.0"]]
  :main ^:skip-aot ring-server.core
  :target-path "target/%s"
  :profiles {:uberjar {:aot :all}})
