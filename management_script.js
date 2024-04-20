"use strict";

// Data
const account1 = {
  owner: "D1",
  movements: [200, 450, -400, 3000, -650, -130, 70, 1300],
  pin: 5207,
  movementsDates: [
    "2019-11-01T13:15:33.035Z",
    "2019-11-30T09:48:16.867Z",
    "2019-12-25T06:04:23.907Z",
    "2020-01-25T14:18:46.235Z",
    "2020-02-05T16:33:06.386Z",
    "2023-05-12T14:43:26.374Z",
    "2023-06-17T18:49:59.371Z",
    "2023-06-20T12:01:20.894Z",
  ],
};

const account2 = {
  owner: "D2",
  movements: [5000, 3400, -150, -790, -3210, -1000, 8500, -30],
  pin: 2222,
  movementsDates: [
    "2019-11-18T21:31:17.178Z",
    "2019-12-23T07:42:02.383Z",
    "2020-01-28T09:15:04.904Z",
    "2020-04-01T10:17:24.185Z",
    "2020-05-08T14:11:59.604Z",
    "2020-05-27T17:01:17.194Z",
    "2020-07-11T23:36:17.929Z",
    "2020-07-12T10:51:36.790Z",
  ],
};

const account3 = {
  owner: "D3",
  movements: [200, -200, 340, -300, -20, 50, 400, -460],
  pin: 3333,
  movementsDates: [
    "2019-11-01T13:15:33.035Z",
    "2019-11-30T09:48:16.867Z",
    "2019-12-25T06:04:23.907Z",
    "2020-01-25T14:18:46.235Z",
    "2020-02-05T16:33:06.386Z",
    "2020-04-10T14:43:26.374Z",
    "2020-06-25T18:49:59.371Z",
    "2020-07-26T12:01:20.894Z",
  ],
};

const account4 = {
  owner: "D4",
  movements: [430, 1000, 700, 50, 90],
  pin: 4444,
  movementsDates: [
    "2019-11-18T21:31:17.178Z",
    "2019-12-23T07:42:02.383Z",
    "2020-01-28T09:15:04.904Z",
    "2020-04-01T10:17:24.185Z",
    "2020-05-08T14:11:59.604Z",
    "2020-05-27T17:01:17.194Z",
    "2020-07-11T23:36:17.929Z",
    "2020-07-12T10:51:36.790Z",
  ],
};

const accounts = [account1, account2, account3, account4];

// Elements
const labelWelcome = document.querySelector(".welcome");
const labelDate = document.querySelector(".date");
const labelWeight = document.querySelector(".balance__value");
const labelSumIn = document.querySelector(".summary__value--in");
const labelSumOut = document.querySelector(".summary__value--out");
const containerMovements = document.querySelector(".movements");

// Functions

// Input Waste Weight
function inputWeight(accountID, weight) {
  const account = accounts.find((acc) => acc.owner === accountID);
  if (account) {
    account.movements.push(weight);
    displayMovements(account);
    updateBalance();
  } else {
    console.log("Account not found!");
  }
}

// Display Movements
function displayMovements(account) {
  containerMovements.innerHTML = "";
  account.movements.forEach((movement, index) => {
    const movementType = movement > 0 ? "deposit" : "withdrawal";
    const date = new Date(account.movementsDates[index]);
    const displayDate = `${date.getDate()}/${
      date.getMonth() + 1
    }/${date.getFullYear()}`;
    const html = `
      <div class="movements__row">
        <div class="movements__type movements__type--${movementType}">${
      index + 1
    } ${movementType}</div>
        <div class="movements__date">${displayDate}</div>
        <div class="movements__value">${movement}Kg</div>
      </div>
    `;
    containerMovements.insertAdjacentHTML("beforeend", html);
  });
}

// Update Balance
function updateBalance() {
  const totalWeight = accounts.reduce((acc, account) => {
    return (
      acc +
      account.movements.reduce((sum, movement) => {
        return sum + movement;
      }, 0)
    );
  }, 0);
  labelWeight.textContent = `${totalWeight}Kg`;
}

// Event listeners
const btnLogin = document.querySelector(".login__btn");
const btnAddWeight = document.querySelector(".form__btn--transfer");
const btnClose = document.querySelector(".form__btn--close");

btnLogin.addEventListener("click", function (event) {
  event.preventDefault();
  const username = document.querySelector(".login__input--user").value;
  const pin = document.querySelector(".login__input--pin").value;
  // Implement login logic here
});

btnAddWeight.addEventListener("click", function (event) {
  event.preventDefault();
  const accountID = document.querySelector(".form__input--to").value;
  const amount = parseFloat(
    document.querySelector(".form__input--amount").value
  );
  inputWeight(accountID, amount);
});

btnClose.addEventListener("click", function (event) {
  event.preventDefault();
  const username = document.querySelector(".form__input--user").value;
  const pin = document.querySelector(".form__input--pin").value;
  // Implement close account logic here
});

// Initialize UI
function init() {
  const currentDate = new Date();
  const formattedDate = `${currentDate.getDate()}/${
    currentDate.getMonth() + 1
  }/${currentDate.getFullYear()}`;
  labelDate.textContent = formattedDate;
  updateBalance();
}

init();
