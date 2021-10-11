import sys
import gzip
import json

day31 = ["01", "03", "05", "07", "08", "10", "12"]
targetEvents = ["PullRequestEvent", "IssueCommentEvent", "WatchEvent"]

output_name = ""
for i in range(1, len(sys.argv)):
    output_name += sys.argv[i] + "-"
output_name = output_name[0:len(output_name)-1] + ".json"
output = open(output_name, "w")

for i in range(1, len(sys.argv)):

    month = sys.argv[i]
    if month == "02":
        for i in range(1, 29):
            day = str(i)
            if len(day) == 1:
                day = "0" + day
            for i in range(0, 24):
                file_name = "2019-" + month + "/2019-" + month + "-" + day + "-" + str(i) + ".json.gz"
                print(file_name)
                g_file = gzip.GzipFile(file_name)
                for line in g_file.readlines():
                    try:
                        line = line.decode("utf-8")
                        line = json.loads(line)
                        if line["type"] == "WatchEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"]}
                            output.write(json.dumps(data))
                            output.write("\n")
                        elif line["type"] == "PullRequestEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"], "payload": {"title": line["payload"]["pull_request"]["title"], "body": line["payload"]["pull_request"]["body"], "labels": line["payload"]["pull_request"]["labels"], "description": line["payload"]["pull_request"]["head"]["repo"]["description"], "language": line["payload"]["pull_request"]["head"]["repo"]["language"]}}
                            output.write(json.dumps(data))
                            output.write("\n")
                        elif line["type"] == "IssueCommentEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"], "payload": {"title": line["payload"]["issue"]["title"], "labels": line["payload"]["issue"]["labels"], "issue_body": line["payload"]["issue"]["body"], "comment_body": line["payload"]["comment"]["body"]}}
                            output.write(json.dumps(data))
                            output.write("\n")
                    except Exception as r:
                        continue

    elif month in day31:
        for i in range(1, 31):
            day = str(i)
            if len(day) == 1:
                day = "0" + day
            for i in range(0, 24):
                file_name = "2019-" + month + "/2019-" + month + "-" + day + "-" + str(i) + ".json.gz"
                print(file_name)
                g_file = gzip.GzipFile(file_name)
                for line in g_file.readlines():
                    try:
                        line = line.decode("utf-8")
                        line = json.loads(line)
                        if line["type"] == "WatchEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"]}
                            output.write(json.dumps(data))
                            output.write("\n")
                        elif line["type"] == "PullRequestEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"], "payload": {"title": line["payload"]["pull_request"]["title"], "body": line["payload"]["pull_request"]["body"], "labels": line["payload"]["pull_request"]["labels"], "description": line["payload"]["pull_request"]["head"]["repo"]["description"], "language": line["payload"]["pull_request"]["head"]["repo"]["language"]}}
                            output.write(json.dumps(data))
                            output.write("\n")
                        elif line["type"] == "IssueCommentEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"], "payload": {"title": line["payload"]["issue"]["title"], "labels": line["payload"]["issue"]["labels"], "issue_body": line["payload"]["issue"]["body"], "comment_body": line["payload"]["comment"]["body"]}}
                            output.write(json.dumps(data))
                            output.write("\n")
                    except Exception as r:
                        continue

    else:
        for i in range(1, 30):
            day = str(i)
            if len(day) == 1:
                day = "0" + day
            for i in range(0, 24):
                file_name = "2019-" + month + "/2019-" + month + "-" + day + "-" + str(i) + ".json.gz"
                print(file_name)
                g_file = gzip.GzipFile(file_name)
                for line in g_file.readlines():
                    try:
                        line = line.decode("utf-8")
                        line = json.loads(line)
                        if line["type"] == "WatchEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"]}
                            output.write(json.dumps(data))
                            output.write("\n")
                        elif line["type"] == "PullRequestEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"], "payload": {"title": line["payload"]["pull_request"]["title"], "body": line["payload"]["pull_request"]["body"], "labels": line["payload"]["pull_request"]["labels"], "description": line["payload"]["pull_request"]["head"]["repo"]["description"], "language": line["payload"]["pull_request"]["head"]["repo"]["language"]}}
                            output.write(json.dumps(data))
                            output.write("\n")
                        elif line["type"] == "IssueCommentEvent":
                            data = {"type": line["type"], "actor": {"id": line["actor"]["id"], "login": line["actor"]["login"], "url": line["actor"]["url"]}, "repoOwner": {"login": line["repo"]["name"].split('\\')[0], "url": "https://api.github.com/users/" + line["repo"]["name"].split('\\')[0]}, "created_at": line["created_at"], "payload": {"title": line["payload"]["issue"]["title"], "labels": line["payload"]["issue"]["labels"], "issue_body": line["payload"]["issue"]["body"], "comment_body": line["payload"]["comment"]["body"]}}
                            output.write(json.dumps(data))
                            output.write("\n")
                    except Exception as r:
                        continue

output.close()