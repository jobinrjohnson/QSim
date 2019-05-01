var cacheName = 'qsim';
var filesToCache = [
  '/',
  '/web/jquery.js',
  '/web/chart.js',
  '/web/app.js'
];
self.addEventListener('install', function (e) {
  e.waitUntil(
    caches.open(cacheName).then(function (cache) {
      return cache.addAll(filesToCache);
    })
  );
});
self.addEventListener('activate', event => {
  event.waitUntil(self.clients.claim());
});
self.addEventListener('fetch', event => {
  event.respondWith(
    caches.match(event.request).then(response => {
      return response || fetch(event.request);
    })
  );
});