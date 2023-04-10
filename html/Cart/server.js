import cors from "cors";
import https from "https";
import fs from "fs";
import express from "express";
import dotenv from "dotenv";
import stripe from "stripe";

// Load variables
dotenv.config();

// Start Server
const app = express();

app.use((req, res, next) => {
  res.header('Access-Control-Allow-Origin', '*'); // Change to your domain in production
  res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
  next();
});

app.use(express.static("public"));
app.use(express.json());

// Home Route
app.get("/", (req, res) => {
  res.sendFile("index.html", { root: "../sterlingcad" });
});

// Success
app.get("/success", (req, res) => {
  res.sendFile("success.html", { root: "../sterlingcad" });
});

// Cancel
app.get("/cancel", (req, res) => {
  res.sendFile("cancel.html", { root: "../sterlingcad" });
});

// Stripe
let stripeGateway = stripe(process.env.stripe_api);
let DOMAIN = process.env.DOMAIN;

app.post("/stripe-checkout", async (req, res) => {
  const lineItems = req.body.items.map((item) => {
    const unitAmount = parseInt(item.price.replace(/[^0-9.-]+/g, "") * 100);
    console.log("item-price:", item.price);
    console.log("unitAmount:", unitAmount);
    return {
      price_data: {
        currency: "usd",
        product_data: {
          name: item.title,
          images: [item.productImg],
        },
        unit_amount: unitAmount,
      },
      quantity: item.quantity,
    };
  });
  console.log("lineItems:", lineItems);

  // Create Checkout Session
  const session = await stripeGateway.checkout.sessions.create({
    payment_method_types: ["card"],
    mode: "payment",
    success_url: `${DOMAIN}/success.html`,
    cancel_url: `${DOMAIN}/cancel.html`,
    line_items: lineItems,
    // Asking Address In Stripe Checkout Page
    billing_address_collection: "required",
  });
  res.json(session.url);
});

// Start the HTTP server on port 3000
const httpPort = 3000;
app.listen(httpPort, () => {
  console.log(`HTTP server is running on port ${httpPort}`);
});
