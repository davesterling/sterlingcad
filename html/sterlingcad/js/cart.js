const payBtn = document.querySelector(".btn-buy");

payBtn.addEventListener("click", () => {
  fetch("https://sterlingcad.com/nodeapp/stripe-checkout", {
    method: "post",
    headers: new Headers({ "Content-Type": "application/json" }),
    body: JSON.stringify({
      items: JSON.parse(localStorage.getItem("cartItems")),
    }),
  })
    .then((res) => res.json())
    .then((url) => {
      // Send a message to the parent window to request redirection
      window.parent.postMessage({ redirectUrl: url }, '*');
    })
    .catch((err) => console.log(err));
});
