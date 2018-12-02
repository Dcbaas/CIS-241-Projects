#/usr/bin/bash

function create_student_dirs(){
  OLD_IFS=IFS
  IFS=$'\n'
  for F in $(ls temp/ -1)
  do
    echo $(echo $F | gawk -F_ '{print $NF}') #change this to just store the name and the last part of the line to another var
    #Check the username to create a folder
    #check the last bit for the regular expression
    #Write the file to the folder, rename to memo if needed
  done
}

echo "What is the zip file name?\n"
read filename
final_folder=$(echo "$1" | gawk -F. '{print $1}')

#unzip $filename -d temp

#mkdir grading
create_student_dirs


