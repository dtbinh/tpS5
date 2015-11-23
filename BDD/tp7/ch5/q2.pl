schema([ename, ssn, bdate, adress, dnumber, dname, dmgrssn]).
fds1([ [[ssn], [ename, bdate, adress, dnumber]]  ]).
fds2([ [[dnumber], [dname,dmgrssrn]] ]).
