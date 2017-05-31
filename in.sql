create table Team (
	History integer,
	Location varchar(30) not null,
	TName varchar(20),
	WinningNumber integer,
	Court varchar(30) not null,
	primary key (TName)
);

create table Player (
	PSSN varchar(9),
	PName varchar(20) not null,
	Birth date,
	Possition varchar(10) not null,
	PNumber integer not null,
	EnterTime integer,
	TName varchar(20) not null,
	FOREIGN KEY (TName) REFERENCES Team (TName) on delete cascade on update cascade, 
	primary key(PSSN)
);

create table Conch (
	CSSN varchar(9),
	CName varchar(20) not null,
	WholeGuide integer,
	TName varchar(20) not null,
	FOREIGN KEY (TName) REFERENCES Team (TName) on delete cascade on update cascade, 
	primary key (CSSN)
);

create table Boss (
	BSSN varchar(9),
	BName varchar(20) not null,
	Value integer,
	TName varchar(20) not null,
	FOREIGN KEY (TName) REFERENCES Team (TName) on delete cascade on update cascade, 
	primary key (BSSN)
);

create table BestArray (
	BType integer not null,
	PSSN varchar(9),
	Time date,
	FOREIGN KEY (PSSN) REFERENCES Player (PSSN) on delete cascade on update cascade, 
	primary key (PSSN)
);

create table Award (
	AName varchar(20),
	Time date,
	PSSN varchar(9) not null,
	FOREIGN KEY (PSSN) REFERENCES Player (PSSN) on delete cascade on update cascade, 
	primary key (AName)
);

create table Game (
	GID varchar(10),
	During integer,
	HostPlace varchar(30) not null,
	HostTime date not null,
	TeamOne varchar(20) not null,
	TeamTwo varchar(20) not null,
	Score varchar(10) not null,
	INDEX(Score),
	FOREIGN KEY (TeamOne) REFERENCES Team (TName) on delete cascade on update cascade, 
	FOREIGN KEY (TeamTwo) REFERENCES Team (TName) on delete cascade on update cascade, 
	primary key (GID)
);

create table Performance (
	PSSN varchar(9),
	GID varchar(10),
	Point integer default 0,
	Assist integer default 0,
	Rebound integer default 0,
	Block integer default 0,
	Steal integer default 0,
	INDEX(Point),
	FOREIGN KEY (PSSN) REFERENCES Player (PSSN) on delete cascade on update cascade, 
	FOREIGN KEY (GID) REFERENCES Game (GID) on delete cascade on update cascade, 
	primary key (PSSN, GID)
);

create view showAvg as
select PName, avg(Point) as avg_point, avg(Assist) as avg_assist, avg(Rebound) as avg_rebound,
avg(Block) as avg_block, avg(Steal) as avg_steal
from Player natural join Performance group by PName;
