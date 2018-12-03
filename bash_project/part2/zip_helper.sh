#/usr/bin/bash

function create_student_dirs(){
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
      echo -n ""
    else
      mkdir grading/$student
      echo "created $student"
    fi

    #Transfer the file to the correct directory
    if [ $argc -eq 4 ]
    then
      mv -u temp/$F grading/$student/memo.txt
    else
      mv -u temp/$F grading/$student/$filename
    fi

    #The memo file will always have one less seperator (4) than the 
    #rest of them so that is the check for the file
    #transfer the files

    #check the last bit for the regular expression
    #Write the file to the folder, rename to memo if needed
  done
  IFS=$OLD_IFS
}

#promt and get the zip filename from the user
echo "What is the zip file name?\n"
read filename
#$final_folder=$(echo "$1" | gawk -F. '{print $1}')

#unzip the files and throwaway the output.
unzip $filename -d temp >throwaway

mkdir -p grading
create_student_dirs

rm -rf temp
rm throwaway 
