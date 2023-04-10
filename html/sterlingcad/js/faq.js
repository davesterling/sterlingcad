



   
    function toggleAccordion(element) {
      element.classList.toggle('expanded');
    }
    
    


























function toggleFuzzyGlow() {
    const buttons = document.querySelectorAll('button');
    buttons.forEach(button => {
      if (window.innerWidth < 770) {
        button.classList.add('fuzzy-glow');
      } else {
        button.classList.remove('fuzzy-glow');
      }
    });
  }
  window.addEventListener('resize', toggleFuzzyGlow);
  /*Tabs*/
  const tabs = document.querySelectorAll('.tab');
  const sections = document.querySelectorAll('.section');
  
  tabs.forEach(tab => {
    tab.addEventListener('click', () => {
      const target = tab.dataset.target;
      sections.forEach(section => {
        section.classList.remove('active');
      });
      document.querySelector(target).classList.add('active');
      tabs.forEach(tab => {
        tab.classList.remove('active');
      });
      tab.classList.add('active');
    });
  });
        // Tabbed content functionality
        const tabButtons = document.querySelectorAll('.tab-button');
        const tabContents = document.querySelectorAll('.tab-content');
        function switchTab(tab) {
          tabButtons.forEach(button => button.classList.remove('active'));
          tabContents.forEach(content => content.classList.remove('active'));
          tab.classList.add('active');
          const content = document.querySelector(`.tab-content[data-tab="${tab.dataset.tab}"]`);
          content.classList.add('active');
        }
        tabButtons.forEach(button => button.addEventListener('click', () => switchTab(button)));
  
  
  
  
  
  
  
  
  
  
  
  
  window.onload = function () {
    google.accounts.id.initialize({
      client_id: '335082268909-jrmq8d9jsg37qd7t995d67a9l6u1q88e.apps.googleusercontent.com',
      callback: handleCredentialResponse
    });
    google.accounts.id.prompt();
  };
  
  
   id="g_id_onload"
  data-client_id="335082268909-jrmq8d9jsg37qd7t995d67a9l6u1q88e.apps.googleusercontent.com"
  data-context="signup"
  data-login_uri="https://sterlingconglomerate.com"
  data-auto_select="true"
  data-itp_support="true">
  
  <pre id="content" style="white-space: pre-wrap;"></pre>
   type="text/javascript"
    
    const CLIENT_ID = '335082268909-jrmq8d9jsg37qd7t995d67a9l6u1q88e.apps.googleusercontent.com';
    const API_KEY = 'a4c95364a0442f011a8bcb5462f7d1839830e990';
  
    const SCOPES = 'https://www.googleapis.com/auth/spreadsheets';
  
    let tokenClient;
    let gapiInited = false;
    let gisInited = false;
  
  
  
    function gisLoaded() {
      tokenClient = google.accounts.oauth2.initTokenClient({
        client_id: CLIENT_ID,
        scope: SCOPES,
      });
  
    }
  
   
    function handleAuthClick() {
      tokenClient.callback = async (resp) => {
        if (resp.error !== undefined) {
          throw resp;
        }
        await appendUserData();
      };
  
      tokenClient.requestAccessToken({ prompt: 'consent' });
    }
  
  
    function handleCredentialResponse(response) {
  
  console.log("Encoded JWT ID token: " + response.credential);
  }
  window.onload = function () {
  google.accounts.id.initialize({
  client_id: "335082268909-jrmq8d9jsg37qd7t995d67a9l6u1q88e.apps.googleusercontent.com", 
  callback: handleCredentialResponse 
  });
  
    function handleSignoutClick() {
      const token = gapi.auth.getToken();
      if (token !== null) {
        google.accounts.oauth2.revoke(token.access_token);
        gapi.auth2.getAuthInstance().signOut().then(() => {
          document.getElementById('content').innerText = '';
          document.getElementById('authorize_button').style.visibility = 'visible';
          document.getElementById('signout_button').style.visibility = 'hidden';
        });
      }
    }
  
    async function appendUserData() {
      const spreadsheetId = '1lHKLgpi5QhrkV10XyxqXH2gZ8ovbnFfCFLOktwpQC1s';
      const range = 'Sheet1';
  
      const user = gapi.auth2.getAuthInstance().currentUser.get();
    }
    }
  
  
  
  
  
  
  
  
  
    for (var i = 0; i < 1000; i++) {
      document.write("<br>");
    }