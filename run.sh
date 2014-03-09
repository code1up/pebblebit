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
# pebble install --pebble_id 00:17:EC:D6:4B:01
# pebble install
# pebble logs

