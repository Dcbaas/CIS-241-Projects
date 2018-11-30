#/usr/bin/bash

#A string to mssage how much was backed up
numbackup=""

#The message that will say what files were backed up
backupmssg=""

#Checks to see if the backup folder exist. If it doesn't then 
#a new one is created in the home directory.
#No params.
#No return.
check_backup(){
  if ! [ -d ~/backup/ ]
  then
    echo "No backup"
    mkdir ~/backup
  fi
}

#Displays a help message to the user and exits the program.
#No param.
#No returns.
display_help(){
  echo "This program backs up files to a backup directory in the home folder"
  echo "Usage: backup [options] sourceDir|sourceFileList"
  echo "-s: silences all outputs indicating which files have been copied over to backup"
  echo "-c: prints numbers on how many files were and were not copied over"
  echo "--help prints the help text to the user (Don't know why you need to know this since you seem to have got here fine)"
}

#Copies a file into the backup folder and echos a message into the backup message.
#Param Folder path: The folder path to the files.
#param The file name itself.
#param The string for the output message.
copy_file(){
  cp -v -u $1$2 ~/backup/. 
}

#Takes a directory and extracts the list of files from the folder and calls
#the copy_files function on them.
#Param: Directory Name
handle_dir(){
  path=$1
  files=$(ls $1)
  set $files

  for var in $@
  do
    copy_file $path $var
  done

  exit 0
}

#Checks the user input list to see if an input is a file or a directory.
#If its a file, then the file is copied over directly. If its a folder
#the handle_dir function is called. If its an invalid input then the 
#program stops.
#param input param from user
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

