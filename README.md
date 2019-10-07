INNAN DU SPELAR:
Alla spelfiler (och Makefile) ligger i mappen "states". I definitions.h måste man ändra sökvägen till filerna från det LIU-id som står 
till sitt egna LIU-id för att det ska gå att öppna filerna. Exempel: 
     
"/home/ponja383/alla-4/Resources/Sprites/rottenZombietexture.png"
       ^^^^^^^^
Ändra detta till ditt egna LIU-id!

********
SPELGUIDE: 
*Spelets mål är att skydda slottet nere i högra hörnet från fiender. Genom att placera torn längs den gråa stigen kan man döda fienderna. 
*Det finns fyra olika torn: Power Tower, Fast Tower, Ice Tower och Water Tower.
     *Power Tower är det billigaste tornet. Har inga speciella egenskaper, det skjuter långsamt, kort och hårt.
     *Fast Tower är det näst billigaste tornet. Det har längre räckvidd än Power Tower, skjuter snabbare men gör mindre skada per skott.
     *Ice Tower är det näst dyraste tornet. Skotten saktar ner fienden i 2 sekunder. Det har lika lång räckvidd som Fast Tower. Är inte direkt top 3 dps om man säger så. 
     *Water Tower är det dyraste tornet. Det har lång räckvidd, mycket hög skada och lika lång reload som Ice Tower. Kan dock endast byggas i vattnet i vänstra hörnet. 

*Varje torn kan uppgraderas obegränsat många gånger, det blir dock dubbelt så dyrt varje gång. Uppgraderingen ökar alltid tornets skada, vissa levels får tornet även högre räckvidd eller snabbare reload time. 
*Släpper man igenom en vanlig fiende (zombie, fladdermus eller sheepman) förlorar slottet 1 hp. Släpper man igenom bossen, som spawnar var tionde level, förlorar man 5 hp. Man börjar med 10 hp, och när ens liv når 0 förlorar man spelet.


********
BUGG:
En sällsynt bugg vi upptäckt är att man ibland inte "plockar upp" ett torn när man klickar på det i shoppen. När detta händer är det bara att högerklicka på musen innan man försöker placera det på kartan. Placerar man tornet ändå så    kommer den Tile man placerade ut tornet på att tro att den är upptagen av ett torn, och således vara obyggbar resten av spelet. 
