#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"

jeah madafakkka

int cas();
int razlikaCasa(int zacetni,int koncni,int sec);
int pretvoriCrke(int vnos,int dolzina);
int jeStevilka(int vnos,int dolzina);
int symbol(int vnos,int dolzina);
int addToSms(int vnos,int dolzina,char SMS[]);
int dolzinaTipke(char tipka);
int number(char tipka);
int beri(int *zacetniCas,char SMS[]);


/*
 * Prebira telefonske tipke od uporabnika in jih dodaja SMS-ju dokler ni SMS daljsi od 160 znakov ali 
 * dokler uporabnik ne pritisne na tipko ENTER (10 ascii)
 */
int main(void){
  char SMS[160] = ""; //Spremenljivka, ki bo vsebovala sms
  int dolzina,vnos,bralec,zacetek;
  do{
    bralec = beri(&zacetek,SMS);//Prebere znak iz tipkovnice in zabelezi cas kdaj je bil znak vnesen
  }while(!number(bralec));
  vnos = bralec;
  dolzina = 1;
  addToSms(bralec,dolzina,SMS);//Doda vnesen znak SMS-ju
  while(strlen(SMS)<160 && bralec != 10){
    bralec = beri(&zacetek,SMS);//Prebere znak iz tipkovnice in zabelezi cas kdaj je bil znak vnesen
    if(number(bralec)){
      if(bralec==vnos && !razlikaCasa(zacetek,cas(),5)){//Preveri, ce uporabnik je pritisnil drugacno tipko ali je minilo vec kot 5 sekund od prejsnjega vnosa
	dolzina=dolzina % dolzinaTipke(vnos);
	dolzina++;
	SMS[strlen(SMS)-1] = '\0';//Zbrise zadnji znak niza
      }
      else{
	dolzina = 1;
	vnos = bralec;
      }
      addToSms(bralec,dolzina,SMS);//Doda vnesen znak SMS-ju
    }
    else if(bralec==127){
      SMS[strlen(SMS)-1] = '\0';//Zbrise zadnji znak niza
    }
  }
  system("clear");
  printf("--NEW SMS--\n%s\n-----------\n",SMS);
  return 0;
}

/*
 *Prebere znak iz tipkovnice in postavi cas v trenutku vnosa v spremenljivko na katero kaze kazalec *zacetniCas
 */
int beri(int *zacetniCas,char SMS[]){
  *zacetniCas = cas();
   system("clear");
   printf("--NEW SMS--\n%s",SMS);
   return getch();
}

/*
 *Vrne 0 ce podana tipka ne spada pod telefonskimi tipkami 
 */
int number(char tipka){
  if(tipka>47 && tipka<58){return 1;}
  return 0;
}

/*
 *Vrne maksimalno stevilo znakov za podano tipko
 */
int dolzinaTipke(char tipka){
  if(tipka==49 || tipka==55 || tipka==57){
    return 5;
  }
  if(tipka==48){
    return 3;
  }
  else{
    return 4;
  }
}

/*
 *Pretvori podano tipko v pripadajoc znak in doda znak SMS-ju
 */
int addToSms(int vnos,int dolzina,char SMS[]){
  int num;
  int dolzinaSMS = strlen(SMS);
  if(jeStevilka(vnos,dolzina)){
    num=vnos;
  }
  else if((num = symbol(vnos,dolzina))){}
  else{
    num = pretvoriCrke(vnos,dolzina);
  }
  SMS[dolzinaSMS] = num;
  SMS[dolzinaSMS+1] = '\0';
  return 0;
}

/*
 *Vrne cas (sekunde), ki je minil od 1. januarja 1970
 */
int cas(){
  FILE *f = popen("date +%s","r");
  int datum;
  fscanf(f,"%d",&datum);
  pclose(f);
  return datum;
}

/*
 *Izracuna razliko med podanima casoma
 */
int razlikaCasa(int zacetni,int koncni,int sec){
  if((koncni-zacetni) >= sec){
    return 1;
  }
  return 0;
}

/*
 *Vrne 1, ce pritisnjene tipke pripadajo stevilki
 */
int jeStevilka(int vnos,int dolzina){
  if((dolzina == 4) && (vnos != 48) && (vnos != 49) && (vnos != 55) && (vnos != 57)){
      return 1;
  }
  if(dolzina == 2 && vnos == 48){
      return 1;
  }
  if(dolzina == 5){
      return 1;
  }  
  return 0;
}

/*
 * Podano tipko pretvori v znak
 */
int symbol(int vnos,int dolzina){
  switch (vnos)
  {
  case 48:
    switch (dolzina){
      case 1:return 32; //Vrne prostor             
      case 3:return 10; //Vrne znak za novo vrsto  
    }
  case 49:
    switch (dolzina){
      case 1:return 46;  //Vrne piko
      case 2:return 44;  //Vrne vejico
      case 3: return 33; //Vrne klicaj
      case 4: return 63; //Vrne uprasaj
    }
    
  }
  return 0;
}

/*
 *Vrne pripadajoc znak za podane pritisnjene tipke
 */
int pretvoriCrke(int vnos,int dolzina){
  int i,pozicija=0;
  vnos -=48;
  for(i=2;i<vnos;i++){
    if(i==7){
      pozicija ++;
    }
    pozicija +=2;
  }
  pozicija += dolzina + 94 + vnos;
  return pozicija;
}
