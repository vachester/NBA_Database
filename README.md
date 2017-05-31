# NBA\_Database

### 介绍

&emsp;&emsp;顾名思义，这是个数据库系统，基于`mySQL`关系数据库，并且用QT工具做出了图形界面，功能比较简单，数据也较为简略。该数据库系统主要是记录NBA常规赛的一些精彩的比赛，以及各个奖项的得主，每场比赛球员的得分以及比赛的比分。


### 实体

* Team(TName ,History,Location,Court,,WinningNumber)，属性分别代表的含义是球队名字，球队创建年份，球队所在地，球馆，获取的总冠军数
* Player(PSSN,PName,Birth,EnterTime,PNumber,Possition)，属性分别代表的含义是社会安全号码，球员名字，进入联盟年份，号码，打球的位置(如PF)
* Conch(CSSN,CName,WholeGuide)，属性分别代表的含义是社会安全号码，教练名字，执教生涯年数
* Boss(BSSN,BName,Value)，属性分别代表的含义是社会安全号码，老板的名字，老板的身价
* BestArray(BType,Time)，属性分别代表的含义是最佳阵容类型，最佳阵容公布时间
* Award(AName,Time)，属性分别代表的含义是奖项的名字，奖项颁布的公布时间
* Game(GID,HostTime,HostPlace,During)，属性分别代表的含义是比赛的标识，比赛举行时间，比赛举行地点，持续时间
* Result(TeamOne,TeamTwo,Score)，属性分别代表的含义是球队1的名字，球队2的名字，球队1和球队2的比分

### 关系

* guide：Conch-Team，1对1，表示球队的教练
* belong\_to：Boss-Team，1对1，表示球队的老板
* play\_for：Player-Team，N对1，表示球员属于某个球队
* grant：BestArray-Player，1对N，最佳阵容名单
* honored：Award-Player，1对1，奖项得主
* game\_result：Game-Result，N对1，比赛的结果
* take\_part\_in：Player-Game，N对N，球员在比赛中的表现，其中关系的属性有：Point，Rebound，Assist，Block，Steal

> 可以参考我上传的ER图
