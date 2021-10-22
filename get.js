const https = require('https');
let cnt = 0;
setInterval(() => {
    https.get('https://www.noi.cn/xw/2019-08-16/715365.shtml', res => {
        console.log(`Got resp: ${res.statusCode}`);
        res.resume();
        cnt++;
        console.log(cnt);
    }).on('error', e => {
        console.log('err');
    });
}, 5000);