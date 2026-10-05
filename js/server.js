const http = require('http');
const fs = require('fs');
const { spawn } = require('child_process');

// abre o programa em C uma única vez
const atm = spawn('./atm');
let saida = '';
atm.stdout.on('data', (dados) => { saida += dados.toString(); });

const servidor = http.createServer((req, res) => {
    if (req.method === 'GET') {                       // entrega a página
        res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
        res.end(fs.readFileSync('index.html'));
        return;
    }

    let corpo = '';                                   // POST: recebe o texto digitado
    req.on('data', (parte) => { corpo += parte; });
    req.on('end', () => {
        saida = '';
        atm.stdin.write(JSON.parse(corpo).texto + '\n'); // manda para o C
        setTimeout(() => {                            // espera o C responder
            res.writeHead(200, { 'Content-Type': 'application/json; charset=utf-8' });
            res.end(JSON.stringify({ resposta: saida }));
        }, 200);
    });
});

servidor.listen(3000, () => console.log('Abra http://localhost:3000'));