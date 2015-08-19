. env.sh

# Build.
pebble build

if [ $? -ne 0 ]
then
	exit 1
fi

# Clear slot and install.
pebble rm 2
sleep 2
pebble install
pebble logs
