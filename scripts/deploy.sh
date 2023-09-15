screen --version &&

# Flash Arduino
echo "flashing Arduino..." &&
(cd ../arduino/sketches && make deploy) &&


# Start Flask in background
echo "launching Flask in background..." &&
( \
  pkill screen
  cd ../brain/src/flask &&
  read -p 'Enter ip address: ' LOCAL_IP &&
  screen -dmS robot_flask &&
  screen -S robot_flask -X stuff "source ../../../../venv/bin/activate && flask run --host=$LOCAL_IP\n" &&
  screen -ls \
) &&

echo "done."
