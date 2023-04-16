/*----------------------------------------------------------------------------------------------------------------------------------------------------
.                                                       "TIMBRE AUTOMATIZADO PARA COLEGIO"
. Por Tomás Caratti - tomircaratti@gmail.com
. (Para horarios de tuno mañana, (Secundario) y turno tarde (Terciario)
                                        
.        Conexion RTC:  Arduino UNO    GND-->GND  VCC-->5V  SCL-->SCL  SDA-->SDA
.        Conexion Rele: Arduino UNO    GND-->GND  VCC-->5V  IN-->10

.        NOTA: se debe cargar dos veces este programa   1. Con la linea RTC.adjust(DateTime(__DATE__, __TIME__));
.                                                       2. Sin esa linea con "//" delante de la lina,
.                                                          para que quede en comnetario y no se cargue nuevamente
------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;                              // inicializa el modulo RTC
const int activador = 10;                    // Pin 10 encargado de activar el timbre, se conecta al Rele
int r_diaSemana;                             // almacena el resultado del dia de la semana calculado
int segundo;
int minuto;
int hora;

/*----------------------------- Durecion timbre Corto y Largo ------------------------------*/
int timbre_corto = 2000;
int timbre_largo = 5000;         // Tiempo continuo que dura sonando (en milisegundos 5000 = 5 seg)
/*-------------------------------------------------------------------------------------------
Hora en la que suena el timbre escrito  h1=Hora, m1=Minutos, s1=Segundos
Cuando no se programa ninguna hora se debe dejar escrito el numero 99  
Se pueden programar 16 timbres

-------------- Horarios Timbres Secundario Mañana de Lunes a Jueves -------------*/

int h1_c1=15;   int m1_c1=23;   int s1_c1=0;   int h1_c1_largo=true;
int h2_c1=15;   int m2_c1=24;  int s2_c1=0;   int h2_c1_largo=false;
int h3_c1=15;   int m3_c1=25;  int s3_c1=0;   int h3_c1_largo=true;
int h4_c1=15;   int m4_c1=25;  int s4_c1=0;   int h4_c1_largo=false;
int h5_c1=15;   int m5_c1=26;  int s5_c1=0;   int h5_c1_largo=true;
int h6_c1=99;  int m6_c1=0;  int s6_c1=0;   int h6_c1_largo=true;
int h7_c1=99;  int m7_c1=0;  int s7_c1=0;   int h7_c1_largo=true;
int h8_c1=99;  int m8_c1=0;  int s8_c1=0;   int h8_c1_largo=true;
int h9_c1=99;  int m9_c1=0;  int s9_c1=0;   int h9_c1_largo=true;
int h10_c1=99; int m10_c1=0;  int s10_c1=0;   int h10_c1_largo=true;
int h11_c1=99; int m11_c1=0;  int s11_c1=0;   int h11_c1_largo=true;
int h12_c1=99; int m12_c1=0;  int s12_c1=0;   int h12_c1_largo=true;

/*-------------------------------- Void Setup() --------------------------------*/
void setup () { 
 pinMode(activador, OUTPUT);                     // Configura como salida el pin 10
 
 Serial.begin(9600);                             // Establece la velocidad de datos del puerto serie a 9600

 if (! rtc.begin ()) {                           // Inicia la comunicación con el RTC, si no se logra comunicación, muestra error y no sigue.
  Serial.println ("Modulo RTC no encontrado!");
  while (1);
 }
 Wire.begin();
 
//rtc.adjust(DateTime(__DATE__, __TIME__));
/* Lee la fecha y hora del PC (Solo en la primera carga) se usa solo en la configuracion inicial, luego se pone como comentario.
Se vuelve a cargar el programa sin esta linea */
} 

/*-------------------------------- Void loop() --------------------------------*/
void loop(){
  DateTime now = rtc.now();                   // Obtiene la fecha y hora del RTC
  
  Serial.print(now.day(), DEC);               // Dia
  Serial.print('/');
  Serial.print(now.month(), DEC);             // Mes
  Serial.print('/');
  Serial.print(now.year(), DEC);              // Año
  Serial.print(' ');
  Serial.print(now.hour(), DEC);              // Horas
  Serial.print(':');
  Serial.print(now.minute(), DEC);            // Minutos
  Serial.print(':');
  Serial.print(now.second(), DEC);            // Segundos
  Serial.println();

  segundo = now.second();
  minuto = now.minute();
  hora = now.hour();

  int r_diaSemana = dia_de_semana();            // llama a la funcion que calcula el dia de la semana y lo almacena en r_diaSemana
  if (r_diaSemana == 6 || r_diaSemana == 0){   // si es fin de semana no hace nada   
  }else {
    horario_1();                              // llama a la funcion que activa el horario 1
    //horario_2();                              // llama a la funcion que activa el horario 2
   }
  digitalWrite(activador, LOW);                    // apaga el timbre
  delay(1000);                                  // La información se actualiza cada 1 seg.
}

/*-------------------------------- Funcion que activa el Timbre -------------------------------*/

void activar_timbre(int largo_timbre){
  digitalWrite(activador, HIGH);  
  Serial.println("Timbre Activo");
  delay(largo_timbre);
  }

/*-------------------------------- Calcula el dia de la Semana -------------------------------*/

int dia_de_semana(){                         // Encuentra el dia de la semana de una fecha

 int n_dia;
 int r_dia;
 int n_mes;
 int t_mes;
 int n_anno;
 int d_anno;
 int t_siglo = 6;

 DateTime now = rtc.now();                   //fecha y hora del RTC

 n_anno = (now.year()-2000);
 d_anno = n_anno/4;
 n_dia = now.day();
 n_mes = now.month();

 switch (n_mes) {
    case 1:
      t_mes=0;
      break;
    case 2:
      t_mes=3;
      break;
    case 3:
      t_mes=3;
      break;
    case 4:
      t_mes=6;
      break;
    case 5:
      t_mes=1;
      break;
    case 6:
      t_mes=4;
      break;
    case 7:
      t_mes=6;
      break;
    case 8:
      t_mes=2;
      break;
    case 9:
      t_mes=5;
      break;
    case 10:
      t_mes=0;
      break;
    case 11:
      t_mes=3;
      break;
    case 12:
      t_mes=5;
      break;
    default: 
      t_mes=t_mes;
    break;
 }

 r_dia = n_dia + t_mes + n_anno + d_anno + t_siglo;
 r_dia = r_dia % 7;

 switch (r_dia) {
    case 1:
        Serial.print(" Lun ");
      break;
      case 2:
       Serial.print(" Mar ");
      break;
      case 3:
       Serial.print(" Mie ");
      break;
      case 4:
       Serial.print(" Jue ");
      break;
      case 5:
       Serial.print(" Vie ");
      break;
      case 6:
       Serial.print(" Sab ");
      break;
      case 0:
       Serial.print(" Dom ");
      break;
      default:
       Serial.print(" ---");
      break;
 } 
 return r_dia; 
}

/*-------------------------------- Condicional del Horario 1 -------------------------------*/

void horario_1(){
   Serial.print("Sec.Mañ:L-J ");
   if ((hora==h1_c1) && (minuto==m1_c1) && (segundo==s1_c1)) {
    if (h1_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h2_c1) && (minuto==m2_c1) && (segundo==s2_c1)) {
    if (h2_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h3_c1) && (minuto==m3_c1) && (segundo==s3_c1)) {
    if (h3_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h4_c1) && (minuto==m4_c1) && (segundo==s4_c1)) {
    if (h4_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h5_c1) && (minuto==m5_c1) && (segundo==s5_c1)) {
    if (h5_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h6_c1) && (minuto==m6_c1) && (segundo==s6_c1)) {
    if (h6_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h6_c1) && (minuto==m6_c1) && (segundo==s6_c1)) {
    if (h6_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h7_c1) && (minuto==m7_c1) && (segundo==s7_c1)) {
    if (h7_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h8_c1) && (minuto==m8_c1) && (segundo==s8_c1)) {
    if (h8_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h9_c1) && (minuto==m9_c1) && (segundo==s9_c1)) {
    if (h9_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h10_c1) && (minuto==m10_c1) && (segundo==s10_c1)) {
    if (h10_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h11_c1) && (minuto==m11_c1) && (segundo==s11_c1)) {
    if (h11_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
   if ((hora==h12_c1) && (minuto==m12_c1) && (segundo==s12_c1)) {
    if (h12_c1_largo==true) { activar_timbre(timbre_largo); }
    else{ activar_timbre(timbre_corto); }
   }
}