Transactional Key Value Store project done for a job interview.

<h1>Commands:</h1>

	SET <key> <value> // store the value for key
	GET <key>         // return the current value for key
	DELETE <key>      // remove the entry for key
	COUNT <value>     // return the number of keys that have the given value
	BEGIN             // start a new transaction
	COMMIT            // complete the current transaction
	ROLLBACK          // revert to state prior to BEGIN call 

<h1>Build:</h1>

	git clone https://github.com/mortinger91/Transactional-Key-Value-Store
	cd Transactional-Key-Value-Store
	mkdir build
	cd build
	cmake ..
