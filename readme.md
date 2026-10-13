Dette er prosjektet mitt i TDT4102 for våren 2025.

Dette programmet lar brukeren sende inn en tekstfil med et sudokubrett. Brukeren kan velge om hen vil bare få
løst brettet kjapt eller om hen vil se en visualisering av løsningsprossesen i et AnimationWindow. AnimationWindow er en klasse i et bibliotek fra faget og kan brukes til å tegne enkle former.

### Metode

Programmet lagrer informasjon om hver celle i en klasse som heter Block. Block klassen inneholder et sett av muligheter som ligger i possibleNumbers variabelen. Når et sudokubrett blir initialisert, inneholder dette settet alle tall mellom 1 og 9. Metoden for eliminere muligheter i hver block ligger for det meste i funksjonene i improveCluster.h.
En ”Cluster” er en vector med pekere til blocks. Det kan være en rad, en
kolonne eller en 3x3 boks i brettet. Måten funksjonene i improveCluster be-
grenser mulighetene er ved å se på alle mulige subsets av blocker i clusteren på en viss størrelse. Deretter ser programmet på unionen av alle mulighetene i blockene i subsetet. Dersom størrelsen på unionen av muligheter er like stor
som størrelsen på subsetet kan programmet slette de tallene fra mulighetene i alle andre blockene i clusteret.
Denne metoden er ikke perfekt og det finnes brett som den ikke greier å
løse. Når jeg har testet den på brett fra sudoku.com så har den funket på alle
vanskelighetsgradene utenom den aller vanskeligste, extreme. Jeg hadde egentlig
tenkt til å implementere funksjonalitet som gjorde at når solveren stopper
skulle den gjette en løsning og fortsette prosessen og backtracke dersom det
viste seg at den løsningen var feil. Dette fikk jeg ikke tid til.

### Solverklassen og Eventlistener
Solverklassen er den som sørger for at funksjonene i improveCluster bli applisert
riktig på sudokubrettet. I tillegg til å inneholde en peker til brettet inneholder
den også en vector med pekere til eventListeners. Det finnes to typer subklasser
av eventListener; GraphicEventListener og LoggingEventListener. Disse to inneholder de samme funksjonene, men gjør forskjellige ting. LoggingEventListener skriver til terminalen, mens GraphicEventListener tegner brettet i et AnimationWindow og viser løsningsprosessen. Gjennom løsningsprosessen kaller
solveren på disse funksjonene med å bruke std::for_each.