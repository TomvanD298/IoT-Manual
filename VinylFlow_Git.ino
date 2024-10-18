
#include <ESP8266WiFi.h>


#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <SpotifyArduino.h>
#include <SpotifyArduinoCert.h>
#include <ArduinoJson.h>



// ------- Replace the following! ------

char clientId[] = "CLIENTID";     // Your client ID of your spotify APP
char clientSecret[] = "CLIENTTOKEN"; // Your client Secret of your spotify APP (Do Not share this!)

#define WIFI_SSID "NAME" //Name of wifi
#define WIFI_PASSWORD "PASSWORD" //Password of Wifi

#define SPOTIFY_MARKET "IE"
#define SPOTIFY_REFRESH_TOKEN "REFRESHTOKEN"

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "TELEGRAM_BOTTOKEN"
const unsigned long BOT_MTBS = 1000; // mean time between scan messages

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure telegramClient;
WiFiClientSecure spotifyClient;
UniversalTelegramBot bot(BOT_TOKEN, telegramClient);
SpotifyArduino spotify(spotifyClient, clientId, clientSecret, SPOTIFY_REFRESH_TOKEN);

unsigned long bot_lasttime; // last time messages' scan has been done
unsigned long delayBetweenRequests = 60000; // Time between requests (1 minute)
unsigned long requestDueTime; //time when request due

void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying)
{
    // Use the details in this method or if you want to store them
    // make sure you copy them (using something like strncpy)
    // const char* artist =

    Serial.println("--------- Currently Playing ---------");

    Serial.print("Is Playing: ");
    if (currentlyPlaying.isPlaying)
    {
        Serial.println("Yes");
    }
    else
    {
        Serial.println("No");
    }
    Serial.println();


    Serial.print("Album: ");
    Serial.println(currentlyPlaying.albumName);
    Serial.print("Track: ");
    Serial.println(currentlyPlaying.trackName);

    Serial.println("Artists: ");
    for (int i = 0; i < currentlyPlaying.numArtists; i++)
    {
        Serial.print("  Name: ");
        Serial.println(currentlyPlaying.artists[i].artistName);
    }
}

void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
    Serial.println(bot.messages[i].text);
    bot.sendMessage(bot.messages[i].chat_id, "Hi, How ya doin?", "");
  }
}

void checkSpotifyPlaying()
{
    if (millis() > requestDueTime)
    {
        Serial.print("Free Heap: ");
        Serial.println(ESP.getFreeHeap());

        Serial.println("getting currently playing song:");
        int status = spotify.getCurrentlyPlaying(printCurrentlyPlayingToSerial, SPOTIFY_MARKET);

        if (status == 200)
        {
            Serial.println("Successfully got currently playing");
        }
        else if (status == 204)
        {
            Serial.println("Doesn't seem to be anything playing");
        }
        else
        {
            Serial.print("Error: ");
            Serial.println(status);
        }

        // Update wanneer de volgende Spotify-aanvraag mag plaatsvinden
        requestDueTime = millis() + delayBetweenRequests;  // Voeg wachttijd toe voor de volgende aanvraag
    }
}


void checkTelegramMessages()
{
    // Controleer of het tijd is om nieuwe berichten op te halen
    if (millis() - bot_lasttime > BOT_MTBS)
    {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while (numNewMessages)
        {
            Serial.println("got response");
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }

        bot_lasttime = millis();  // Update laatste Telegram-check tijd
    }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  telegramClient.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  #if defined(ESP8266)
    spotifyClient.setFingerprint(SPOTIFY_FINGERPRINT);
#elif defined(ESP32)
    spotifyClient.setCACert(spotify_server_cert);
#endif

}


void loop()
{
    // Controleer Telegram-berichten
    checkTelegramMessages();  // Roep de nieuwe functie aan

  // Controleer Spotify "currently playing" status
    checkSpotifyPlaying();  // Roep de Spotify controle functie aan
}

