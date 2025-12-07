# V1
- make crud of user & post
- use sqlitecpp

# V2
- add auth
- add logging
- use postgres

# V3
- refactor user & post into models

app
- init
- set config
- get db
- init services
- activate logging
- register routes
- app port run

models
- user: name, email, passhash; crud, getset
- post: title, content, author, created_at, publish_status; crud, getset

routes
middleware: auth, logging
services: user, posts (eg: autogrnerate post content)
docs: api

# V4
- add persistence (redis, cache)
- add storage