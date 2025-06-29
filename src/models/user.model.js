import mongoose, {Schema} from "mongoose";
import mongooseAggregatePaginate from "mongoose-aggregate-paginate-v2";
import bcrypt from "bcrypt"
import { use } from "react";


const userSchema = new Schema({
    username : {
        type : String ,
        required : true,
        unique : true,
        lowercase : true,
        trim : true,
        index : true
    },
    email : {
        type : String ,
        required : true,
        unique : true,
        lowercase : true,
        trim : true
    },
    Fullname : {
        type : String ,
        required : true,
        trim : true,
        index : true
    },
    avatar : {
        type : String ,
        required : true
    },
    coverImage : {
        type : String
    },
    watchHistory : [
        {
            type : Schema.Types.ObjectId,
            ref : "Video"
        }
    ],
    password : {
        type : String,
        required : [true , 'Password is required']
    },
    refreshToken : {
        type : String
    }
},
    {
        timestamps : true
    }

)

videoSchema.pluggin(mongooseAggregatePaginate)

userSchema.pre("save" , async function(next){
    if(!this.isModified("password")) return next();
    this.password = bcrypt.hash(this.password , 10)
    next()
})

userSchema.methods.isPasswordCorrect = async function(password){
    return await bcrypt.compare(password , this.password)
}

userSchema.methods.generateAccessToken = function(){
    Jwt.sign(
        {
            _id : this._id,
            email : this.email,
            username : this.username,
            Fullname : this.Fullname
        },
        process.env.ACCESS_TOKEN_SECRET,
        {
            expiredIn : process.env.ACCESS_TOKEN_EXPIRY
        }
    )
}
userSchema.methods.generateRefreshToken = function(){
    Jwt.sign(
        {
            _id : this._id
        },
        process.env.REFRSH_TOKEN_SECRET,
        {
            expiredIn : process.env.REFRSH_TOKEN_EXPIRY
        }
    )
}


export const User = mongoose.model("User" , userSchema)