#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#define RX 7
#define TX 6
char c;
int X=18;
int red=0;
int green=0;
int blue=100;
int mov=1;
int ancmov=1;
int i=0;
bool centre=false;
int player[7][4]={{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}};  // {numero de la bande de led, mov, coefficient pour avancer ou reculer,ancmov}
bool mode;
int choice=0;
bool chosen=false;
int y=0;
int tour=0;
int choix=0;

SoftwareSerial blueT(RX,TX);
Adafruit_NeoPixel font[] = {Adafruit_NeoPixel(10, 10, NEO_GRB + NEO_KHZ800),Adafruit_NeoPixel(10, 9, NEO_GRB + NEO_KHZ800),Adafruit_NeoPixel(10, 8, NEO_GRB + NEO_KHZ800)};
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(X, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(X, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(X, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(X, 5, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip[4]={strip1,strip2,strip3,strip4};



int etat[4]={1,1,1,1};

void setup() {
  // put your setup code here, to run once:
  for(int i=0; i<4; i++) strip[i].begin();
 
  
  Serial.begin(9600);
  for(int u=0;u<4;u++){
  for(int i=0;i<X;i++){
          strip[u].setPixelColor(i,0,0,0);
  }
  
 
  strip[u].show();}
  
    Serial.begin(9600);
    delay(500);
  blueT.begin(9600);
 
  for(int i =0; i<3; i++){
  font[i].begin();
  font[i].show(); // Initialise toute les led à 'off'
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:
  float timer=micros();
  while(micros()-timer<38400){
    
  }
  // choisi une fonction selon la fonction changer_mode()
  if(choice==1)
    chemins_en_action();
  else if(choice==2)
     deplacement();
  else
     perso_in_jardin ();
  if(choix==1)
    fontaine();
  else
    fontaine_reel();
  
   
  
  
}

void fontaine(){
  char f=char(blueT.read());
  while (chosen)
    changer_mode();
  if (f=='p')
    chosen=true;
  for(int z=0; z<255; z++){
    for(int i = 0; i < 10; i++ ) { // On fait une boucle pour définir la couleur de chaque led
        // setPixelColor(n° de led, Rouge, Vert, Bleu)
        font[(y+2)%3].setPixelColor(i, 255-z, z, 0);
        font[(y+1)%3].setPixelColor(i, 0, 255-z, z);
        font[(y)%3].setPixelColor(i, z, 0, 255-z);
    }
    for(int i =0; i<3;i++)
    font[i].show();
    delay(1);
  }
  y++;
}

void fontaine_reel(){
  char f=char(blueT.read());
  while (chosen)
    changer_mode();
  if (f=='p')
    chosen=true;
   for(int i =0; i<10;i++){
      int rnd = random(0, 100);
      font[(y+2)%3].setPixelColor(i+(y%10), rnd , rnd, 200);
      font[(y+1)%3].setPixelColor(i+(y%10), rnd, rnd, 200);
      font[y%3].setPixelColor(i+(y%10), rnd, rnd, 200);
    }
    for(int i =0; i<3;i++)
    font[i].show();
    y++;
}

void chemins_en_action(){
  //while(blueT.available()){
    if(chosen){
    changer_mode();
  }
    c= char(blueT.read());
    
    switch(c){
      case 'p':
        chosen=true;
        break;
     
      case 'k':
        etat[0]=1-etat[0]; //met l'etat de la bande à on/off
        break;
      case 'q':
        etat[1]=1-etat[1];
        break;
      case 'a':
        red=blueT.parseInt(); // permet de choisir le nombre correspondant à la couleur rouge
        break;
      case 'b':
        blue=blueT.parseInt();
        break;
      case 'c':
        green=blueT.parseInt();
        break;
      case 'm':
        etat[2]=1-etat[2];
        break;
      case 't':
        etat[3]=1-etat[3];
        break;
    }
          for(int y =0;y<4;y++){
            if(!etat[y]){ // eteint toutes les led à l'etat off
              for(int u=0;u<X;u++){
                strip[y].setPixelColor(u,0,0,0);
                
                strip[y].show();
            }}
            else{// allume toutes les led à l'etat on
              for(int v=0;v<X;v++){
                strip[y].setPixelColor(v,red,blue,green);
                
                strip[y].show();
              }
            
            
          }
    
 }
   
}
void eteindre(int led){ //eteint la bande de led en parametre
  strip[led].setPixelColor(0,0,0,0);
  strip[led].show();
}


void center(int mov){// indique le centre du bloc central
  if(mov==-1)
    centre=true;
  
}

int choix_au_centre(){// change le chemin quand on se situe au centre du du bloc 
  float timer2=micros();
  while(micros()-timer2<3800){
    
  }
  
  char choix=char(blueT.read());
  
    switch(choix){
      case 'l':
        eteindre(i);
        i=2;
        centre=false;
        break;
      case 's':
        eteindre(i);
        i=3;
        centre=false;
        break;
      case 'r':
        eteindre(i);
        i=0;
        centre=false;
        break;
      case 'h':
        eteindre(i);
        i=1;
        centre=false;
        break;
  }
 
}


void deplacement(){
  
  if(centre){
    choix_au_centre();
  }
  while(chosen){
    changer_mode();
  }
  char d=char(blueT.read());
  
  switch(d){
    case 'p':
      chosen=true;
      break;
    case 'l':
      if(mov<=X && (i==3 || i==2)){//deplacement sur deux bandes de led adjacentes (avance)
        ancmov=mov;
        mov+=1;
        }
        center(mov);
      break;
    case 's':
      if(mov<=X && (i==3 || i==2)){//de meme mais recule cette fois-ci
        ancmov=mov;
        mov-=1;
        }
        center(mov);
      break;
    case 'r':
       if(mov<=X && (i==1 || i==0)){// on change de groupe de bandes
        ancmov=mov;
        mov+=1;
       }
       center(mov);
       break;
    case 'h':
      if(mov<=X && (i==1 || i==0)){
        ancmov=mov;
        mov-=1;
      }
      center(mov);
      break;
    default:
      break;
  }
  if(mov>=-1){// avancement sur une bande
    strip[i].setPixelColor(mov,red,blue,green);
    strip[i].setPixelColor(ancmov,0,0,0);}
  if(mov<-1){// avancement sur la bande adjacente
    strip[i].setPixelColor(-(mov+2),red,blue,green);
    strip[i].setPixelColor(-(ancmov+2),0,0,0);
  }

    strip[i].show();
     
}

void perso_in_jardin(){
  char f=char(blueT.read());
  while (chosen) //permet de changer de mode quand chosen = true
    changer_mode();
  if (f=='p')
    chosen=true;
  int limites=X;
  
  for(int k=0;k<7;k++){// on a 7 personnages 
    for(int j=0;j<4;j++){// ils avances sur les 4 chemins
      if(player[k][0]==j && abs(player[k][1])>X) on verifie qu'il ne depasse pas les limites du chemin si oui on change la direction
        player[k][2]=-player[k][2];
      
    }
    
   if(player[k][0]==player[1-k][0] && player[k][1]==player[1-k][1])// si 2 personnages se croisent ils changent de direction
     player[k][2]=-player[k][2];
   center(player[k][1]);//on verifie si il est au centre
   player[k][3]=player[k][1]; // meme principe que ancmov = moc
   player[k][1]+=1*player[k][2]; //on multiplie par le coefficient pour reculer ou avancer
   if(centre){// changement de chemin au centre
    player[k][0]=random(0,4);
    centre=false;
   }
   if(player[k][1]>=-1){
    strip[player[k][0]].setPixelColor(player[k][1],red,blue,green);
    strip[player[k][0]].setPixelColor(player[k][3],0,0,0);
   }
   if(player[k][0]<-1){
    strip[player[k][0]].setPixelColor(-(player[k][1]+2),red,blue,green);
    strip[player[k][0]].setPixelColor(-(player[k][3]+2),0,0,0);
   }//avancement sur les bandes adjacentes
   


   
   
   
      
}
   for(int h=0;h<7;h++){
      strip[player[h][0]].show();   
      delay(10);
   }
   
}


void changer_mode(){
  
  char d=char(blueT.read());
  switch(d){// on coisit un mode selon le bouton il renvoie une lettre differente
    case 'z':
      choice=1;
      
      break; 
    case 'y':
      choice=2;
      
      break;
    case 'x':
      choice=0;
      
      break;
     
  }
  if(d=='w'){
    choix=0;
    chosen=false;
  }
  else if(d=='v'){
    choix=1;
    chosen=false;
  }
    
  for(int u=0;u<4;u++){// on eteint les led du mode precedent
  for(int i=0;i<X;i++){
          strip[u].setPixelColor(i,0,0,0);
  }
  strip[u].show();}
    
  }
  
