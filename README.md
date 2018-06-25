...**chapter** logo...

## TODO
+ Support location for appropriate `.git` directory location for project
+ Check last committed that is not on remote (current branch)
+ Integrate with an open source proof-reading tool (e.g https://github.com/bakwc/JamSpell)
+ Execute audit program on a `post-commit` hook 
+ Add a config file for supporting rules (default includes all rules)
+ Option to ignore and push regardless of errors
+ Add terminal UI for progress and success/errors
+ Setup test suite
+ Update `README.md`: ToC, project name, overview, and add logo
+ Add GitHub badge to be downloaded (similar to Prettier)

## NOTES
+ [How to Write a Git Commit Message (Chris Beams)](https://chris.beams.io/posts/git-commit)
+ [Commit Message Guidelines](https://gist.github.com/robertpainsi/b632364184e70900af4ab688decf6f53)
+ [What makes a good commit message (hackernoon)](https://hackernoon.com/what-makes-a-good-commit-message-995d23687ad)
+ [Writing good commit messages](https://github.com/erlang/otp/wiki/writing-good-commit-messages)
+ [Whats with the 50/72 rule](https://medium.com/@preslavrachev/what-s-with-the-50-72-rule-8a906f61f09c)
+ [Character Encodings](http://www.idevelopment.info/data/Programming/character_encodings/PROGRAMMING_character_encodings.shtml)

## Overview
..

## Installation
+ Move executable in `$HOME/bin` (?)
+ Update bash script for `post-commit`
+ Ensure permissions are set `chmod +x .git/hooks/post-commit`
+ Add ability to install via `brew`
+ ...

### JSON helper
+ `brew tap nlohmann/json` && `brew install nlohmann_json`

## Usage
+ How to run script manually
+ Run option `--verbose` for more details on commands
+ ...

## Rules
+ Show example of warning/error
+ Rule in `COMMIT_MSG_RULES.json`
+ ...

### Typos
...

### Summary capitalization
...

### Summary length
+ Positive integers only
+ ...

### Description required
...

### Description length
...

### Bullet points required
...

### Documentation format
...

### Nit format
...

### WIP format
...

### Rules TODO
+ JSON file (or alike for C++ projects)
+ No-typos
+ Max-character length
+ Capitalization of each sentence
+ Require summary (character length)
+ Require X bullet points (hyphen, astericks, plus)
+ Explicit rule for `Nit: ...` and `WIP:...` (format, character length)
+ Require UTF-8 characters
+ No Emoji
+ Include JIRA ticket number

## Future
See [TODO.md](https://github.com/williamgrosset/chapter/blob/master/TODO.md).

## Contributing 
See [CONTRIBUTING.md](https://github.com/williamgrosset/chapter/blob/master/CONTRIBUTING.md).

## Integration 
Chapter is integrated into this repository at commit message [#154](https://github.com/williamgrosset/chapter.git).

## License
[MIT](https://github.com/williamgrosset/chapter/blob/master/LICENSE)
