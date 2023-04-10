// Hide header on scroll down
var prevScrollpos = window.pageYOffset;
window.onscroll = function() {
  var currentScrollPos = window.pageYOffset;
  if (prevScrollpos > currentScrollPos) {
    document.getElementById("header").style.top = "0";
  } else {
    document.getElementById("header").style.top = "-80px";
  }
  prevScrollpos = currentScrollPos;
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