<h1>IoT-Manual VinylFlow</h1>
  <p>This is a manual to connect my NODEMCU ESP8266 to the spotify API. My goal is to get information or the lyrics from a specific song or artist.<br>
    I want to communicate with the node via Telegram. If everything works well, I also want to display the current song on an LCD screen.
  </p>

 <h2>Table of content</h2> 
 <ul>
   <li>Spotify API</li>
   <li>Connect Node with Telegram</li>
   <li>Connect your node with spotify</li>
   <li>Combine everything</li>
   <li>Add the LCD</li>
   <li>Troubleshooting</li>
 </ul>

<section>
<h2>Spotify API</h2>
<p>
The first step is to create an API token from Spotify. You can do this by logging in at https://developer.spotify.com/dashboard. If you don’t have an account yet, create one. It’s free. <br>
</p>
<p>Klik bij onderstaand scherm op "Create App"</p>
<img width="600" alt="Screenshot 2024-10-17 at 11 29 11" src="https://github.com/user-attachments/assets/9bc05827-1060-41e7-aa42-4b22066dfb41">
<br><br>
<p>Next, you fill in the following fields and hit save at the end of the form:</p>
<ul>
  <li>
    <b>Under API/SDKs, select the Web API.</b>
  </li>
  <li>
    <p>For <b>Redirect URIs (required)</b>, I entered the link to my GitHub, but you can change this later if needed.</p>
  </li>
</ul>
<img width="600" alt="Screenshot 2024-10-17 at 11 43 52" src="https://github.com/user-attachments/assets/89997423-6b0d-4180-bec3-0e5ee891c9c1">

<p>When youre done, i should look like this</p>
<img width="400" alt="Screenshot 2024-10-17 at 12 05 16" src="https://github.com/user-attachments/assets/cda4ea99-f796-4e4d-9124-66242e61771e">
<p>In the dashboard, click on the app.</p>
<p>In the right upper corner, select "Settings"</p>
<p>Here you can find your "Token".  It is hidden under the "Find client secret" tab. You will need this later.</p>
<img width="400" alt="Screenshot 2024-10-17 at 12 10 01" src="https://github.com/user-attachments/assets/4fa0e705-c6ae-409c-a808-3a7093ff0da9">
</section>


<section>
<h2>Telegram Token</h2>
<p> For this step, you need Telegram. In Telegram, you can create a bot that you can then link to your Node. This allows you to send messages to your Node. </p>
<img width="125" alt="image" src="https://github.com/user-attachments/assets/0f1f0bc5-e74f-47d6-964d-44a59fe136b9">

<ol>
  <li>
    Download Telegram and create an account there.  
  </li>
  <li>
    Search for the user: "The BotFather" and add them.  
  </li>
  <li>
    Type /newbot to create a new one.  
  </li>
  <li>
    Give it a random name (I named mine VinylFlow).  
  </li>
  <li>
    Then give it a username; it must be unique and end with "bot." (Mine is named VinylFlowBot).
  </li>
  <li>
    Now you will receive a token. Make sure to keep this for later. <br>
    This is a personal token; do not share it online.
  </li>
</ol>
</section>

<section>
<h2>Connect Node with Telegram</h2>
<ol>
<li> 
<p> Add the UniversalTelegramBot library. You will see the option below; choose to install everything.</p>
<img width="105" alt="image" src="https://github.com/user-attachments/assets/57d2d372-3840-44df-8b80-4da3dc228cc1">
<img width="350" alt="image" src="https://github.com/user-attachments/assets/44bae65a-443e-49e0-a227-d87e5af340e8">
 <p> And add "ArduinoJson" by Benoit Blanchon, not the beta version, but the latest version.</p> 
</li>
  
<li>
  Open the test file "EchoBot." Do this by clicking on File > Examples > UniversalTelegramBot (scroll all the way down) > esp8266 > EchoBot.
  <b>Make sure you are using ESP8266 and not ESP32.</b><br>
  <p><b>ESP32 will not work. (Took me half an hour to realise this)</b></p>
</li>

<li>
Modify the code on lines 26 to 30 as follows:<br>
<img width="589" alt="Screenshot 2024-10-17 at 13 24 54" src="https://github.com/user-attachments/assets/77599c86-21f7-4868-b088-467445e30d3f"><br>
Enter the token you received when creating your bot on line 30.
</li>

<li>
  Now, connect your NodeMCU to your computer.
</li>

<li>
  <p>Upload the code to your Node to check if your Wi-Fi is working. Open your Serial Monitor to see if it’s functioning. I encountered the following issue:</p>
  <img width="452" alt="image" src="https://github.com/user-attachments/assets/ef7843bf-7b3e-45f7-9629-017d04e1eea9">
 <p>You can solve this by simply disconnecting the Node and reconnect it.</p>
</li>
<li>
  Then, you need to change the Baud rate from 9600 (default) to 115200. You can do this in the serial monitor on the right.
  <img width="452" alt="image" src="https://github.com/user-attachments/assets/cd802055-cd96-4500-a7f8-1f59f1aded94">
</li>
<li>
 <p> Then, write in the code on line 43:</p>
  <code>Serial.println(bot.messages[i].text);</code><br>
  <p>This will print the text you send via Telegram in your Serial Monitor.</p>
</li>

<li>
  <p>Then, you can add the following line below it:</p>
  <code>bot.sendMessage(bot.messages[i].chat_id, "Hi, How ya doin?", "");</code><br>
  <p>This will ensure that you receive a response to your text.</p>
</li>
</ol>
</section>

<section>
<h2>Connect your node with spotify</h2>
  <p>To connect with Spotify, I am using the Spotify API from <a href="https://github.com/witnessmenow/spotify-api-arduino">witnessmenow</a>.</p>
  <p>There is a full blown tutorial how to connect with the API. There were a few steps I struggled with, which I will explain below:</p>
 <h3>Library</h3> 
<ol>
  <li>
    <p>I used <a href="https://roboticsbackend.com/install-arduino-library-from-github/">this tutorial</a> to add an libary to my node.</p>
  </li>
  <li>
    <p>The first thing you need to do is download the project from the GitHub of <a href="https://github.com/witnessmenow/spotify-api-arduino">witnessmenow</a>.</p>
    <p>The download button can be found at the "<> Code" button</p>
    <img width="400" alt="Screenshot 2024-10-17 at 21 24 46" src="https://github.com/user-attachments/assets/3d305c05-cd64-4f5e-9578-900d56c753cd">
    <p>You need the ZIP</p>
  </li>
  <li>
    <p>Unzip the file</p>
  </li>
  <li>
    <p>When you're in the Arduino IDE program, click on Files -> Open. This will open the folder where everything is stored. Then, go to the "libraries" folder and paste the entire API project into this directory.</p>
  </li>
  <li>
    <p>Restart your IDE</p>
  </li>
</ol>

  <h3>AccesToken</h3>
  <p>To make the API call, you first need an Refresh Token from Spotify. You can obtain it in the following way:</p>
<ol>      
  <li>Open the getRefreshToken Example. Files -> Examples -> SpotifyArduino -> getRefreshToken</li>
  <li>
    <p>On lines 88-92, you need to fill in your own information. (This includes your Wi-Fi credentials and the tokens you obtained from Spotify in the earlier steps). </p>
     <img width="896" alt="Screenshot 2024-10-17 at 21 38 20" src="https://github.com/user-attachments/assets/e95537ba-7978-49eb-b86a-3fd44e3cadea">
  </li>
  <li>
    <p>The first time I ran the program, I didn’t get anything in the serial monitor. It was simply a matter of disconnecting the Node and reconnecting it to the laptop.</p>
  </li>
  <li>
    <p>Now, you will see an IP address in your serial monitor.</p>
  </li>
  <li>
    <p></p>Add the following to Redirect URI on your Spotify app "http://[ESP_IP]/callback/"<br>
    e.g. "http://192.168.1.20/callback/" (don't forget the last "/")</p>
    <img width="300" alt="Screenshot 2024-10-17 at 21 50 26" src="https://github.com/user-attachments/assets/3ee7c6e4-45a9-4d2e-bfa9-16e7e55a06ce">
    <p>(This is where we added the Github link in the beginning.)</p>
  </li>
  <li>
    <p>Next, type http://192.168.1.20 into your internet browser, replacing (http://192.168.1.20) with the IP address you got from the serial monitor.</p>
  </li>
  <li>
    <p>The page should like like this:</p>
    <img width="200" alt="Screenshot 2024-10-17 at 16 58 15" src="https://github.com/user-attachments/assets/d5cb7a00-9fa2-466e-a794-9c52d486139c">
  </li>
  <li>
    <p>Click on the link, and you will be redirected to Spotify. You need to accept this.</p>
    <img width="393" alt="Screenshot 2024-10-17 at 17 01 59" src="https://github.com/user-attachments/assets/8db21d7d-2233-4de4-9722-9c0425614d31">
  </li>
  <li>
    <p>Now you will receive a long token, which you will need later. This is your **refresh token**!</p>
  </li>

  <h3>Small test</h3>
  <li>
      <p>Open the example file "getCurrentlyPlaying". <br>
      Now, enter your Wi-Fi details here, along with your tokens. You'll also need your **refresh token**, so make sure to enter that as well.<br> If everything works it should look like this:</p>
      <img width="400" alt="Screenshot 2024-10-17 at 21 02 37" src="https://github.com/user-attachments/assets/ce2a48bd-6c00-4f18-a94c-71d14d4956ed">
  </li>
</ol>  
</section>

<section>
  <h2>Linking API and Telegram</h2>
  <p>When I started linking everything, I first put all the code into ChatGPT. Then I stated that I wanted to send the command "Nummer" via Telegram and receive the name of the song in response. This became a big mess, and I didn't understand anything anymore.<br>
After that, I started breaking down the "CurrentPlaying" code until I had the basics working. This part is still functioning.</p><br><br>

<p>Unfortunately, I couldn't get it to link properly. I think the problem lies in the loop. The first time I run the code, it retrieves all the messages from Telegram and then logs the current song. However, now my Telegram messages are no longer coming through. I tried creating separate functions, adding timers, importing tickers, and using those, but none of that worked.</p>
<img width="500" alt="Screenshot 2024-10-18 at 01 20 34" src="https://github.com/user-attachments/assets/0bd2d761-c558-430a-9b07-39b2f4d3f49c">
<img width="500" alt="Screenshot 2024-10-18 at 01 29 50" src="https://github.com/user-attachments/assets/fe99a41d-b48f-4b4a-9ccb-0698f04ec43f">

<p>I also checked if the issue might be related to the certificates or even the routes.</p>
<img width="500" alt="Screenshot 2024-10-18 at 01 32 45" src="https://github.com/user-attachments/assets/b8954379-67fd-45f8-9eac-c708befdd473">
<p>This was not the problem, but it cleaner.</p>
</section>

<section>
  <h2>Connect a screen</h2>
  <p>Despite not being able to link it, I still wanted to see if I could display the current song on an OLED screen that is compatible with Arduino.</p>
</section>

<section>
  <h2>Troubleshooting</h2>
<p> i had some problems myself while making this.</p>
<ol>
  <li>
    <p>I encountered this issue while working with the Telegram bot. Instead of selecting the **ESP8266**, I accidentally chose the **ESP32** from the examples.</p>
    <img width="500" alt="Screenshot 2024-10-17 at 13 44 31" src="https://github.com/user-attachments/assets/f13e0f3b-f9c0-4371-9370-83095877b153">
  </li>
  <li>
    <p>The problem here was that it wasn't clear that you shouldn't include "/callback/" in the browser. Only the IP address should be entered here.</p>
    <img width="300" alt="Screenshot 2024-10-17 at 16 50 30" src="https://github.com/user-attachments/assets/e03b340a-fe97-45ee-b6bb-25b65ed9f928">
    <img width="300" alt="Screenshot 2024-10-17 at 16 50 17" src="https://github.com/user-attachments/assets/cd741a71-6f35-452f-aa17-2c54c8eb677b">
  </li>
  <li>
    <p>Here, my Spotify API was still linked to my GitHub. So, I needed to change this on the Spotify dashboard to the IP and then add "/callback" at the end.</p>
    <img width="300" alt="Screenshot 2024-10-17 at 16 58 21" src="https://github.com/user-attachments/assets/08563eae-c60d-4950-9b60-0ff881e2adad">
  </li>

</ol>
</section>




