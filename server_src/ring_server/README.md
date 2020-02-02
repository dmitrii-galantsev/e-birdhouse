# ring_server

## Installation

Install [Clojure](https://clojure.org/guides/getting_started) and [Leinigen](https://leiningen.org/)

## Usage

Run using leiningen:
    
    $ lein run

Compile a standalone jar file (staticly links everything and packs in a jar):

    $ lein uberjar

Execute standalone jar file:

    $ java -jar ./target/uberjar/ring_server-0.1.0-SNAPSHOT-standalone.jar

## Options

By default the server is started on port 3000. Modify the source to change it.

TODO: Database login

## Examples

### Bugs

...
