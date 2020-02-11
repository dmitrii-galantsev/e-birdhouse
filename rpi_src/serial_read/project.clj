(defproject serial_read "0.1.0-SNAPSHOT"
  :description "read serial and send POST"
  :license {:name "EPL-2.0 OR GPL-2.0-or-later WITH Classpath-exception-2.0"
            :url "https://www.eclipse.org/legal/epl-2.0/"}
  :dependencies [[org.clojure/clojure "1.10.0"]
                 [clj-serial "2.0.5"]]
  :main ^:skip-aot serial-read.core
  :repl-options {:init-ns serial-read.core}
  :target-path "target/%s"
  :profiles {:uberjar {:aot :all}})
