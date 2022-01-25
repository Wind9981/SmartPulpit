var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;
const Http = new XMLHttpRequest();
const url='https://98d46694f428.ngrok.io/home/download?subject=Ng%E1%BB%AF%20V%C4%83n%209&pathfile=on-tap-phan-tieng-viet-lop-9.pdf';
Http.open("GET", url);
Http.send();

Http.onreadystatechange = (e) => {
  console.log(Http.responseText)
}
