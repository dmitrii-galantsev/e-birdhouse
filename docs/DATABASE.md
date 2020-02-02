Database info:

PostgreSQL database is used for the project.

Currently it only uses 1 table in dev stage.

It can be created by calling these commands over `psql`

```
CREATE TABLE dev (
    time  int,
    temp  int,
    hum   int,
    mov   int);
```

Don't forget to expose the database to public network
