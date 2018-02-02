---
layout: page
title: Projects
permalink: /projects/
---
{% highlight java %}
public SupremeBot(Config config)
{
    cfg=config;        
    PROD_SECTION=cfg.getValue("bot.prod_section");
    PROD_NAME=cfg.getValue("bot.prod_name");
    PROD_COLOR=cfg.getValue("bot.prod_color");
    PROD_SIZE=cfg.getValue("bot.prod_size");
    driver = new ChromeDriver();
    f = new File("chromedriver.exe");
    if(!f.exists())
        error("chromedriver.exe not in directory...closing");
    try{
        aRetry=cfg.getValue("bot.AUTORETRY");
    } catch (NullPointerException e) { aRetry="0"; }
    version=0;
}

{% endhighlight %}
