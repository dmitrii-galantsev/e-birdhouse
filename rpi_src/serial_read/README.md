# serial_read

This program reads serial values and sends them to the server
via POST request.

## Installation

Install [Clojure](https://clojure.org/guides/getting_started) and [Leinigen](https://leiningen.org/)

## Usage

Run using leiningen:
    
    $ lein run

Compile a standalone jar file (staticly links everything and packs in a jar):

    $ lein uberjar

Execute standalone jar file:

    $ java -jar ./target/uberjar/serial_read-0.1.0-SNAPSHOT-standalone.jar

## Options

By default the data is read from /dev/ttyACM0. Modify source code to change it.

## Examples

### Bugs

...
