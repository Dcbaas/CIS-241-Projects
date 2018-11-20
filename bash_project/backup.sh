#/usr/bin/bash

check_backup(){
  if ! [ -d ~/backup/ ]
  then
    echo "No backup"
    mkdir ~/backup
  fi
}
display_help(){
  echo "This program backs up files to a backup directory in the home folder"
  echo "Usage: backup [options] sourceDir|sourceFileList"
  echo "-s: silences all outputs indicating which files have been copied over to backup"
  echo "-c: prints numbers on how many files were and were not copied over"
  echo "--help prints the help text to the user (Don't know why you need to know this since you seem to have got here fine)"
}

copy_file(){
  cp -v -u $1 ~/backup/.
  echo "$1 was copied"
}

handle_dir(){
  files=$(ls $1)
  set $files

  for var in $@
  do
    copy_file $var
  done

  exit 0
}

check_input(){
  if [ -d $1 ]
  then
    handle_dir $1
  elif [ -f $1 ]
  then
    copy_file $1
  else
    echo "Error: $1 is not a valid file or directory"
    exit 1
  fi
}


True=true
False=false
silenced=false
viewcp=false

copied=0
notcp=0

#ensure the backup directory exist. Create it if it doesn't
check_backup

for var in $@
do
  echo $var
  case $var in 
    "-s")
      silenced=true
    ;;
    -c)
      viewcp=true
    ;;
  --help)
    display_help
    exit 0
    ;;
  *)
    check_input $var 
    ;;
  esac

done

