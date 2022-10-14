Créer le fichier vide dhcpd.leases (dans var/dhcpd/ ou /etc/ ou ailleur)

Configurer le dhcpd.conf (dans /etc ou ailleur)

Arrèter le network manager local
```shell
sudo /etc/init.d/network-manager stop 
```

Le serveur doit être dans le bon sous réseau
```shell
sudo ifconfig <interface> <ip> netmask <netmask>
```

Lancer le serveur dhcp
```shell
sudo ./dhcpd -f -d  <-cf path-to-dhcpd.conf> <-lf path-to-dhcpd.leases>
```


Supprimer l'ancien dhcpd.lease
```shell
rm /var/lib/dhcp/dhclient.leases
```

Redémarrer l'interface
```shell
sudo ifconfig enp2s0 down
```

Lancer le client
```shell
./dhclient eno2
```