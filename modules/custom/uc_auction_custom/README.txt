
Ubercart Auction
by Garrett Albright - http://drupal.org/user/191212
Sponsored by Precision Intermedia - http://precisionintermedia.com/
 and by Lost Coast Communications

Ubercart Auction bare-bones quickie installation and usage guide!

NOTE: When using this module, it's fairly important that your server has its system clock set to the accurate time. Given that all modern operating systems worth counting can set their clocks according to dedicated time servers on the internet, this probably isn't an issue, but it's worth checking out before you start to use UC Auction anyway - you can't really be too sure about this. If you have SSH access to your Unix/Linux-based server, you can check its time using the `date` command. Try running `date -u` both on your server and on a machine whose time you can trust (perhaps your local machine); this'll print out the time in UTC format (Greenwich time). If the difference between the times on both machines is significantly different - I'll let you decide your own definition of a significant difference here - find out which machine is wrong and why, and if it's the server, get it fixed before going live with UC Auction. If you have enough access to the server to run daemons, then `man ntpd`, man.

If you are in a shared hosting environment, you may need to contact your hosting provider and ask them to re-adjust the clock. If you do not have SSH access to your server, load a phpinfo() page via the Devel module or by creating one yourself. The time according to the server will be printed at the top, in the "System" section. But note that you'll have to take time zones, daylight savings time differences, etc into account when you use this method.

Also, note that site visitors who have inaccurate clocks will not see an accurate countdown of remaining time in an auction if the "Active expiration countdown" feature is enabled. Unfortunately, there's not a whole lot we can do about that without making things less accurate for those that *do* have correctly-set clocks.


So is your server's time set correctly? On with the installation instructions:

1. Install Ubercart's modules (if you haven't already) and the Ubercart Auction module as normal.

2. Configure your Ubercart installation as normal, if you haven't already.

3. Go to Administer > Store Administration > Configuration > Auction settings. (The path is admin/store/settings/auction .) Configure these settings. Of important note are the "Bid increment," "Minimum bid increase" and "Maximum bid increase" values. The default values make sense with the United States Dollar and currencies of similar value per unit, but may be too little or too much in other currencies, and are nonsensical in currencies which do not feature subunits such as cents. Save your configuration.

4. Go to Administer > User management > Permissions (admin/user/permissions) and configure the permissions for the uc_auction module. Note that it's possible to give anonymous users (users which have not logged in) the "place bid" permission, but this is not recommended. Only privileged roles should be given the "delete bids" permission.

5. Create or edit a product you wish to be auctioned. In the "Product information" section, underneath the "List price"/"Cost"/"Sell price" fields, you will now see an "Auction settings" section which is collapsed by default. Expand it and check the "This is an auction" field to have the product be auctioned. Use the "Expiration date and time" field to set the expiration time for the auction. After putting a product up for auction, it's a good idea to use the Stock module to limit that item's quantity to one, if you haven't already; otherwise, the auction winner may be able to buy several of the items at the price they bid, which may not be what you want.

6. Once an auction is active, a history of bids placed on that item can be seen by users in roles with the "view bids" permission. Click on the "Bids" tab to see this list. Alternatively, click on the number of bids in the auction information table on the product's page.

7. All users can see a listing of auctioned items they have bid on by clicking on the "Auctions" tab on their user page. There are three pages of listing: "Active auctions" list items have bid on and which are currently active, and informing them if they are still the high bidder on each item; "Auctions I've won" lists expired auctions that the user has won; and "Auctions I've lost" lists expired auctions that the user has bid upon but has not won.


Ubercart Auction API:

Ubercart Auction now has some API hooks so that you may write modules which interact with it. The uc_auction_api/uc_auction_api.module file should tell you everything you want to know. It's all pretty simple at this point. Note that if it doesn't look like anyone is really using these hooks, I may remove them from the release version of UC Auction, so if you do something waeome (http://waeome.com/) with these hooks, do let me know about it.