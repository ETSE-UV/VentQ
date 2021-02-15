#define RX_PIN D7
#define TX_PIN D8
#define BAUDRATE 9600

#define DHT22_PIN D0

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64

#define R_PIN D5
#define G_PIN D4
#define B_PIN D3

#define CO2_MIDDLE 700
#define CO2_HIGH 1000

#define FIRM_SERVER "tramuntana.uv.es"
#define FIRM_PORT 80
#define FIRM_PATH "/firmware/"
#define FIRM_VER "test"

#define API_SERVER "tramuntana.uv.es"
#define API_PORT 80
#define API_PATH "/co2_measure/"
#define API_TOKEN "9p7bbYTTFtXizDuflh6y"

#define WNN 5 //Number of wssid defined
const char *WSSID[] = {"nmcuco2", "Petit", "Pedro", "ONOTE20", "Thunder"};
const char *WPWD[] = {"n0d3mcuco2", "m1l4gr1n", "golgosuli", "sequia2016", "4Sn2BKYCUVLD7sg86MMR"};

#define ACT_FREC 5000 //Actualization frecuency in milliseconds
#define FIRM_CICLES 6 //Cicles before update firm
