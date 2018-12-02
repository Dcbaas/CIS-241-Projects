#/usr/bin/bash

function create_student_dirs(){
  #I need two types of field sperators for this function. One is the 
  #normal whitespace sperator and the other is a newline only 
  #Seperator. 
  OLD_IFS=IFS
  IFS=$'\n'
  for F in $(ls temp/ -1)
  do
    argc=$(echo $F | gawk -F_ '{print NF}') 
    student=$(echo $F | gawk -F_ '{print $2}')
    filename=$(echo $F | gawk -F_ '{print $NF}')

    #Check if the directory exist. Create it if it doesn't 
    if [ -d grading/$student ]
    then
      echo exist
    else
      mkdir grading/$student
      echo "created $student"
    fi

    #The memo file will always have one less seperator (4) than the 
    #rest of them so that is the check for the file
    #transfer the files

    #check the last bit for the regular expression
    #Write the file to the folder, rename to memo if needed
    IFS=$'\n'
  done
}

echo "What is the zip file name?\n"
read filename
final_folder=$(echo "$1" | gawk -F. '{print $1}')

#unzip $filename -d temp

#mkdir grading
create_student_dirs


