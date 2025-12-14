# V0 [done]
- all in one file
- crud routes
- user & post model
- global map as db
- store as release/v0.1

# V1
- [x] make crud of user & post
- use sqlitecpp
	- [x] add sqlitecpp lib
	- [here] wrap user & post data manipulation with repositories. consider making interface & concepts, use dep inj. rewrite for excersize
	- implement db.cpp, connect and test
	- migrate user & post map into fully db based
- prep crud testing tools

# V2
- use templates, no interfaces
- add auth
- add logging
- use postgres

# V3
- refactor user & post into models

---

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