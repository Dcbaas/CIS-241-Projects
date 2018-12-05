#/usr/bin/bash

#A string to mssage how much was backed up
numbackup=0

touch out_mssg.txt

#Checks to see if the backup folder exist. If it doesn't then 
#a new one is created in the home directory.
#No params.
#No return.
check_backup(){
  if ! [ -d ~/backup/ ]
  then
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

inc_count(){
  if [ -d ~/backup/$1 ]
  then
    echo "$1 already exist" >>out_mssg.txt
  else
    let numbackup++
  fi
}

#Copies a file into the backup folder and echos a message into the backup message.
#Param Folder path: The folder path to the files.
#param The file name itself.
#param The string for the output message.
copy_file(){
  cp -v -u $1$2 ~/backup/. >>out_mssg.txt
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

# Vaariables to enable and disable message output.
silenced=0
viewcp=0

#ensure the backup directory exist. Create it if it doesn't
check_backup

for var in $@
do
  case $var in 
    "-s")
      silenced=1
    ;;
    "-c")
      viewcp=1
    ;;
    "-sc")
      silenced=1
      viewcp=1
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

#Print the copy outputs if the user didn't scilence the output.
if [ $silenced -eq 0 ] 
then
  cat out_mssg.txt
fi

#Display the number of files copied
if [ $viewcp -eq 1 ]
then
  echo "$numbackup file(s) were backed up"
fi

rm out_mssg.txt

exit 0

