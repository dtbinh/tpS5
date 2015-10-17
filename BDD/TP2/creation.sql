drop table if exists catalogue;
drop table if exists articles;
drop table if exists fournisseurs;
drop type if exists colors;

CREATE TYPE colors as  ENUM
	('rouge', 'noir', 'argente', 'opaque', 'cyan', 'magenta', 'vert', 'superjaune', 'rose', 'jaune');

CREATE TABLE Articles(
	aid int primary key,                     
	anom varchar(30) not NULL, 
	acoul colors
);



CREATE TABLE Fournisseurs(
	fid int primary key,
	fnom varchar(30),
	fad varchar(70) unique not NULL
);



CREATE TABLE Catalogue(
	fid int references fournisseurs(fid) on delete cascade on update cascade,  
	aid int references articles(aid) on delete cascade on update cascade,
	prix numeric(8,2) not NULL CHECK(prix>=0)
);
