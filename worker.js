onmessage = function(e) {
    const f = e.data[0];
    FS.mkdir('/work');
    FS.mount(WORKERFS, { files: [f] }, '/work');

    console.log(Module.surfaceReader('/work/' + f.name));
}

self.importScripts('pmread.js');