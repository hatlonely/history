package main

import (
	"context"
	"fmt"
	"github.com/globalsign/mgo/bson"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"time"
)

func main() {
	ctx, _ := context.WithTimeout(context.Background(), 10*time.Second)
	client, err := mongo.Connect(ctx, options.Client().ApplyURI("mongodb://localhost:27017"))
	if err != nil {
		panic(err)
	}

	if err = client.Ping(ctx, readpref.Primary()); err != nil {
		panic(err)
	}

	collection := client.Database("mydb").Collection("mycollection")

	{
		ctx, _ = context.WithTimeout(context.Background(), 5*time.Second)
		res, err := collection.InsertOne(ctx, &bson.M{"name": "pi", "value": 3.14159})
		if err != nil {
			panic(err)
		}
		fmt.Println(res)
	}
	{
		ctx, _ = context.WithTimeout(context.Background(), 30*time.Second)
		cur, err := collection.Find(ctx, bson.M{})
		if err != nil {
			panic(err)
		}
		defer cur.Close(ctx)

		for cur.Next(ctx) {
			var result bson.M
			err := cur.Decode(&result)
			if err != nil {
				panic(err)
			}
			fmt.Println(result)
		}
		if err := cur.Err(); err != nil {
			panic(err)
		}
	}
	{
		ctx, _ = context.WithTimeout(context.Background(), 30*time.Second)
		var result bson.M
		err = collection.FindOne(ctx, bson.M{"name": "pi"}).Decode(&result)
		if err != nil {
			panic(err)
		}
		fmt.Println(result)
	}
}
