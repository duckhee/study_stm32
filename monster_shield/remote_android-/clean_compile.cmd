SET MYMAKE=make
%MYMAKE% clean
rm *.bak
rm *.lst
%MYMAKE% all
pause