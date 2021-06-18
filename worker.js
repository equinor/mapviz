onmessage = function(e) {
    msg = e.data;
    if (msg[0]==="mount"){
        const f = e.data[1];
        FS.mount(WORKERFS, { files: [f] }, '/work')
        console.log(Module.surfaceReader('/work/' + f.name,"pmd"));
        console.log(Module.HEAP16);
    }
}

self.importScripts('pmread.js');
FS.mkdir('/work');