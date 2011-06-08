#!/bin/bash
#
# This command expects to be run within the %project% profile directory. 
#
# To use this command you must have `drush make` installed.
#

if [ -f %project%.make ]; then
  echo -e "\nThis command will download the latest modules included in the %project% install profile and run all pending updates."
  
  if [-d .svn]; then
    svn up
  fi
  # Run openatrium.make only.
  echo "Building %project% install profile..."
  drush make --download-mechanism='drush_make' --working-copy --no-core --contrib-destination=. %project%.make
  drush updatedb
else
  echo 'Could not locate file "%project%.make"'
fi
