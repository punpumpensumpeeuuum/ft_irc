*This project has been created as part of the 42 curriculum by dinda-si, frteixei and marada*

# ft_irc — IRC Server in C++98

---

## Description

**ft_irc** is a fully functional IRC (Internet Relay Chat) server implemented in C++98, built as part of the 42 school curriculum. The goal of the project is to understand and implement low-level network programming concepts — specifically how to create a TCP server capable of handling multiple simultaneous client connections without blocking.

The server follows the IRC protocol and supports client authentication, channel management, operator privileges, and a full suite of standard IRC commands. It is compatible with real IRC clients (tested with tools like `nc` and standard IRC clients).

### Key Features

- Non-blocking I/O with `poll()` for multiplexed connection handling
- Password-protected server authentication
- Full user registration flow (`PASS`, `NICK`, `USER`)
- Channel creation and management with topic, keyword, user limits, and invite-only modes
- Operator privileges and channel moderation (`KICK`, `INVITE`, `MODE`)
- Private and channel messaging (`PRIVMSG`, `NOTICE`)
- Graceful disconnection and signal handling (`SIGINT`, `SIGQUIT`)

---

## Instructions

### Compilation

```bash
make
```

This will produce the `ircserv` binary.

### Running the Server

```bash
./ircserv <port> <password>
```

- `<port>` — A port number between 1024 and 65535
- `<password>` — The server password clients must use to connect

**Example:**
```bash
./ircserv 6667 mypassword
```

### Connecting a Client

You can connect using `nc` (netcat) for quick testing:

```bash
nc localhost 6667
```

Or use any IRC client (e.g. WeeChat, irssi) pointed at `localhost:<port>`.

### Authentication Flow

Once connected, clients must authenticate in this order:

```
PASS <password>
NICK <nickname>
USER <username> * * :<realname>
```

### Available Commands

| Command | Description |
|---|---|
| `HELP` | Show available commands |
| `PASS <password>` | Authenticate with server password |
| `NICK <nickname>` | Set your nickname |
| `USER <user> * * :<realname>` | Set username and real name |
| `JOIN <#channel> [password]` | Join or create a channel |
| `PART <#channel> [reason]` | Leave a channel |
| `PRIVMSG <target> <message>` | Send a message to a user or channel |
| `NOTICE <target> <message>` | Send a notice to a user or channel |
| `TOPIC <#channel> [newtopic]` | View or set a channel topic |
| `KICK <#channel> <user> [reason]` | Kick a user from a channel |
| `INVITE <nick> <#channel>` | Invite a user to a channel |
| `MODE <#channel> <flag> [param]` | Change channel modes |
| `NAMES <#channel>` | List members in a channel |
| `PING <token>` | Ping the server |
| `QUIT [reason]` | Disconnect from the server |

### Channel Modes

| Mode | Description |
|---|---|
| `i` | Invite-only — only invited users can join |
| `t` | Topic lock — only operators can change the topic |
| `k <keyword>` | Set or remove a channel password |
| `l <limit>` | Set or remove a user limit |
| `o <nick>` | Grant or revoke operator status |

---

## Resources

### IRC Protocol & Networking

- [RFC 1459 — Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459) — The original IRC specification
- [RFC 2812 — IRC Client Protocol](https://tools.ietf.org/html/rfc2812) — Updated client protocol reference
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) — Essential resource for socket programming in C/C++
- [`poll()` man page](https://man7.org/linux/man-pages/man2/poll.2.html) — Reference for the I/O multiplexing syscall used in this project
- [IRC Numeric Replies Reference](https://www.alien.net.au/irc/irc2numerics.html) — Complete list of IRC numeric reply codes

### AI Usage

AI (Claude by Anthropic) was used during this project in the following ways:

- **Debugging**: Identifying logic errors in channel/client lifecycle management (e.g. iterator invalidation when erasing channels during disconnect)
- **Code review**: Reviewing edge cases in command parsing and argument validation
- **Documentation**: Generating this README based on the project's source code

AI was not used to generate core implementation logic or to write the server/client/channel classes from scratch.
