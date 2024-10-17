<h1>IoT-Manual VinylFlow</h1>
  <p>This is a manual to connect my NODEMCU to the spotify API. My goal is to get information about a specific song or artist.<br>
    I want to communicate with the node via Telegram. If everything works well, I also want to display the current song on an LCD screen.
  </p>

<h2>Table of content</h2>  
<ul>
  <li>
    <a href="https://github.com/TomvanD298/IoT-Manual#spotify-api">Spotify API </a>
  </li>
  <li>
    <a href="https://github.com/TomvanD298/IoT-Manual#telegram-token">Telegram Token</a>
  </li>
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
</section>


