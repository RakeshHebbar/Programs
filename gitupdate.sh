#To keep all my Git repositories up-to-date:
alias gitupdate='(for l in `find . -name .git | xargs -i dirname {}` ; do cd $l; pwd; git pull; cd -; done)'
