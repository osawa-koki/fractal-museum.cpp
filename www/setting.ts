import Env from './next.config.js'
const isProd = process.env.NODE_ENV === 'production'

const setting = {
  isProd: Env.isProd,
  basePath: Env.basePath,
  apiPath: isProd ? '' : 'http://localhost:8000',
  title: '🌶️ Fractal Museum 🌶️',
  imageSize: '512px'
}

export default setting
