---
layout: single
title:  "Blog Beginnings"
date:   2018-02-01 12:41:43 -0500
categories: jekyll
---
A couple months back, halfway into my first semester at Temple, I found myself in doubt. The first Computer Science class I registered for was CIS 1166 - "Mathematical Concepts in Computing I" - a Discrete Math course. Every section of CIS 1001, the intended introductory CS course, was full by my orientation date, and I had tested out of the first programming class, CIS 1068. This landed me in a classroom full of thick-bearded upperclassmen on my first day of college.

For the first two weeks of class, I watched in horror as the 24-person roster diminished over the first two weeks to a mere 8 survivors. I found myself lost, anxious, and uncertain about my choice of major.

I reached out and asked for advice from a family member, a soon-to-be Computer Science graduate, who took the time to give me a detailed response in which he emphasized one key goal: Make a website and use it wisely. He mentioned that to manage his own site, he runs Jekyll on a Linux VM. I thanked him and stored the advice for when I could give this new project the focus and dedication it needed. After all, I had never worked with Ruby or GitHub in the past, so this was going to be a completely new experience for me.

Two mornings ago, I woke up early, grabbed a large coffee and a breakfast sandwich, and sat down in my dorm with caffeine-fueled determination. I was not going to get up until I had a functioning, attractive site up and running on Github Pages. With something such as Jekyll, this should be an easy setup.

Or so I thought.

Getting Jekyll itself set up was easy enough. I created a local directory, initialized it as a GitHub repo via "git init", cloned it to my computer, and installed Ruby (which I have never used before). After installing the necessary gems to run Jekyll on GitHub Pages, I was ready to generate the Jekyll files and view my fancy new site, and it worked! My site was fully functional on the default Jekyll theme. It took a few more commits to the 'master' branch to get to this point.

The problems began here: I was not a fan of the basic theme. One of the key features of Jekyll is the customization options available to the user, so a change in theme shouldn't have been a difficult task - but it was. After some digging around, I found multiple sources from ~6 months ago claiming that GitHub Pages support is limited, and that when hosting on GitHub pages, there are only a few [supported themes](https://pages.github.com/themes/) available. After browsing through the list, I decided on the "minimal" theme. As per the documentation, I changed my Gemfile to include "gem jekyll-theme-minimal", and adjusted my config.yml accordingly. Jekyll is amazing, I thought to myself! I went to update my gems via "bundle install", and lo and behold, my first roadblock presented itself.

```
Installing ffi 1.9.18 (x64-mingw32)
Gem::RuntimeRequirementNotMetError: ffi requires Ruby version < 2.5, >= 2.0. The
current ruby version is 2.5.0.
An error occurred while installing ffi (1.9.18), and Bundler cannot continue.
Make sure that `gem install ffi -v '1.9.18'` succeeds before bundling.

In Gemfile:
  github-pages was resolved to 172, which depends on
    github-pages-health-check was resolved to 1.3.5, which depends on
      typhoeus was resolved to 0.8.0, which depends on
        ethon was resolved to 0.11.0, which depends on
          ffi
```

Annoying, but not a huge issue, right? Seems like the most recent version of ffi had not yet been updated for Ruby 2.5. Nothing a Google search can't solve. Upon some more digging, I found a [GitHib issue on the ffi repo](https://github.com/ffi/ffi/issues/598) in which multiple users mentioned the same issue; Not all of the users had issues specifically while configuring Jekyll, but one or two did. A solution was posted to install ffi using the -f flag, in which users replied that it had worked. Perfect! So I went to manually force-install ffi, despite the incompatibility with the most recent version of Ruby.

```
$ gem install ffi -f
ERROR: While executing gem ... (ArgumentError) wrong number of arguments (given 1, expected 0)
```
I scratched my head in confusion. The [comment that gave this solution](https://github.com/ffi/ffi/issues/598#issuecomment-354892346) had 25 thumbs up emojis *and* 8 heart emojis - it had to work! This time, my Google-fu lead me nowhere. I decided to move the party to my laptop, and installed an older version of Ruby, cloned my repo, and went to work.

As if a sign from above, I then stumbled upon [this GitHub blog post](https://github.com/blog/2464-use-any-theme-with-github-pages), announcing support for any GitHub hosted Jekyll theme. The steps were supposedly simple, even moreso than before - just add "/$theme_creator/$theme_name" to the config.yml file and rebuild your site, and voila!

However, yet again, simplicity was not in the plans for GitHub Pages today. I built my site locally (via "bundle exec jekyll serve") and navigated to localhost:4000 in Chrome. Nothing. Blank page.
In the terminal sat this monstrosity:
```
Dependency Error: Yikes! It looks like you don't have jekyll-remote-theme or one of its dependencies installed. In order to use Jekyll as currently configured, you'll need to install this gem. The full error message from Ruby is: 'Could not open library 'libcurl': The specified module could not be found. . Could not open library 'libcurl.dll': The specified module could not be found. . Could not open library 'libcurl.so.4': The specified module could not be found. . Could not open library 'libcurl.so.4.dll': The specified module could not be found. ' If you run into trouble, you can find helpful resources at https://jekyllrb.com/help/!
```
Another dependency error, but this time more confusing: Upon running "curl --version", I got a nice clean output informing me that Curl was not only installed, but up to date. Back to Google I went, looking for any way out of this headache. *I should have just used WordPress*, I thought to myself, skimming over the search results looking for anything relevant. I found [this](https://github.com/jekyll/jekyll/issues/6660#issuecomment-354690545) suggestion to use an older version of the github-pages plugin, which only gave me more incompatibility errors. After a while of Googling around, I found [this](https://github.com/benbalter/jekyll-remote-theme/issues/17#issuecomment-354677407) suggestion to move manually extract libcurl.dll from the libcurl installation package, add it to PATH, and copy it to another "libcurl" file, sans .dll extension.

Finally, my page built locally. http://localhost:4000 has never looked so great. I pushed the changes to the master branch, and went to visit my live website.

I was greeted with a cold blank page. *Maybe*, I thought, *it's just the theme*. So I went to install minimal-mistakes using their [QuickStart Guide](https://mmistakes.github.io/minimal-mistakes/docs/quick-start-guide/). Again, blank page. I figured that I had now stumbled upon a layout issue, so I cloned the minimal-mistakes repository and moved all the files over. It worked - upon running the local Jekyll server, everything looked great. Now, back to the live site.

Instead of a blank page, I was now greeted with a boring page lacking any CSS whatsoever. I was dumbstruck - how could my page be building perfectly when running it locally, and completely break when moved to GitHub? I went back to Google and found [this](https://github.com/mmistakes/minimal-mistakes/issues/76) GitHub issue. Upon removing the "s" from "https" in my config, I crossed my fingers and pushed the changes.

Like magic, everything was live and functioning perfectly. It was now two days after I had originally started the project, and I finally had my site up and running. A success in my book.

Thanks for reading.


[jekyll-docs]: https://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
