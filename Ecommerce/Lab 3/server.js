const express = require('express');
const mysql = require('mysql2');
const path = require('path');

const app = express();
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

// MySQL Connection
const db = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: '',
  database: 'ecommerce'
});

db.connect(err => {
  if (err) console.error('DB error:', err);
  else console.log('MySQL Connected...');
});

// Checkout API (using eSewa)
app.post('/api/checkout', (req, res) => {
  const { address, esewaId, email, signature } = req.body;
  const sql = 'INSERT INTO checkouts (address, esewa_id, email, signature) VALUES (?, ?, ?, ?)';
  db.query(sql, [address, esewaId, email, signature], (err) => {
    if (err) return res.status(500).send({ error: 'Checkout failed' });
    res.send({ message: 'Checkout with eSewa verified and saved to MySQL!' });
  });
});

app.listen(3000, () => console.log('Server running on http://localhost:3000'));
