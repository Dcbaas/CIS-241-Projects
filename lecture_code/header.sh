header f1 f2 f3

if[$# -eq 0]

  for i in $*
  do
    #Code here
    grep "#include" $i >>temp
  done
